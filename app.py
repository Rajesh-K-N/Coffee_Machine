# app.py
from flask import Flask, render_template, request, jsonify
import threading
import queue
import time

app = Flask(__name__)

# Global variables to simulate coffee machine state
machine_state = {
    'powered': False,
    'water_level': 0,
    'bean_level': 0,
    'milk_level': 0,
    'temperature': 20,
    'coffees_made': 0,
    'current_state': 'IDLE',
    'max_water': 1000,
    'max_beans': 500,
    'max_milk': 500
}

# Queue for simulating async operations
operation_queue = queue.Queue()

def simulate_machine_operation(operation):
    """Simulate machine operations with delays"""
    if operation == 'power_on':
        machine_state['powered'] = True
        machine_state['current_state'] = 'HEATING'
        time.sleep(3)
        machine_state['temperature'] = 90
        machine_state['current_state'] = 'IDLE'
    
    elif operation == 'power_off':
        machine_state['powered'] = False
        machine_state['current_state'] = 'IDLE'
        machine_state['temperature'] = 20
    
    elif operation == 'fill_water':
        machine_state['water_level'] = machine_state['max_water']
    
    elif operation == 'fill_beans':
        machine_state['bean_level'] = machine_state['max_beans']
    
    elif operation == 'fill_milk':
        machine_state['milk_level'] = machine_state['max_milk']
    
    elif operation.startswith('brew_'):
        coffee_types = {
            'brew_espresso': (30, 9, 0),
            'brew_americano': (120, 9, 0),
            'brew_latte': (30, 9, 150),
            'brew_cappuccino': (30, 9, 120),
            'brew_mocha': (30, 11, 100)
        }
        
        water, beans, milk = coffee_types.get(operation, (0, 0, 0))
        
        if (machine_state['water_level'] >= water and 
            machine_state['bean_level'] >= beans and 
            machine_state['milk_level'] >= milk):
            machine_state['current_state'] = 'BREWING'
            time.sleep(3)
            machine_state['water_level'] -= water
            machine_state['bean_level'] -= beans
            machine_state['milk_level'] -= milk
            machine_state['coffees_made'] += 1
            machine_state['current_state'] = 'IDLE'
    
    elif operation == 'clean':
        machine_state['current_state'] = 'CLEANING'
        time.sleep(5)
        machine_state['coffees_made'] = 0
        machine_state['current_state'] = 'IDLE'
    
    elif operation == 'maintenance':
        machine_state['current_state'] = 'MAINTENANCE'
        time.sleep(4)
        machine_state['current_state'] = 'IDLE'

def operation_worker():
    """Background worker to process machine operations"""
    while True:
        operation = operation_queue.get()
        if operation is None:
            break
        simulate_machine_operation(operation)
        operation_queue.task_done()

# Start operation worker thread
worker_thread = threading.Thread(target=operation_worker, daemon=True)
worker_thread.start()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/status')
def get_status():
    return jsonify(machine_state)

@app.route('/operate', methods=['POST'])
def operate_machine():
    operation = request.json.get('operation')
    operation_queue.put(operation)
    return jsonify({"status": "Operation queued", "operation": operation})

if __name__ == '__main__':
    app.run(debug=True)