"""
You're going to write an interactive calculator! User input is assumed to be a formula that consist of a number, an operator (at least + and -), 
and another number, separated by white space (e.g. 1 + 1). Split user input using str.split(), and check whether the resulting list is valid:

- If the input does not consist of 3 elements, raise a FormulaError, which is a custom Exception.
- Try to convert the first and third input to a float (like so: float_value = float(str_value)). Catch any ValueError that occurs, and instead raise a FormulaError
- If the second input is not '+' or '-', again raise a FormulaError

If the input is valid, perform the calculation and print out the result. The user is then prompted to provide new input, and so on, until the user enters quit.
"""

import Logo


class FormulaError(Exception):
    pass


def get_input(user_input):
    input_list = user_input.split()
    if len(input_list) != 3:
        raise FormulaError('Input does not consist of three elements.')
    n1, op, n2 = input_list
    try:
        n1 = float(n1)
        n2 = float(n2)
    except ValueError:
        raise FormulaError('The first and third input value must be numbers.')
    return n1, op, n2


def calculate(n1, op, n2):
    if op == '+':
        return n1 + n2
    if op == '-':
        return n1 - n2
    if op == '*':
        return n1 * n2
    if op == '**':
        return n1 ** n2
    if op == '/':
        return n1 / n2
    if op == '//':
        return n1 // n2
    raise FormulaError(f'{op} is not a valid operator.')


Logo.name()
while True:
    user_input = input('>>>> ')
    if user_input == 'quit':
        break
    try:
        n1, op, n2 = get_input(user_input)
        result = calculate(n1, op, n2)
        print(result)
    except FormulaError as error:
        # '\033[91m' for red colour and '\033[0m' to reset it to default
        print('\033[91m', f'FormulaError: {error} ', '\033[0m')
