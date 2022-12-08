from machine import Pin
import time

BTN = Pin(27, Pin.IN)
ENCA = Pin(25, Pin.IN)
ENCB = Pin(26, Pin.IN)


def promptUser(msg: str) -> bool:
    resp = input(f'{msg}')
    if resp == 'y':
        return True
    else:
        return False


def btnTest() -> bool:
    default_val = BTN.value()
    print(f'Unpressed button value is: {default_val}')
    msg = 'Enter y if the button is held down, n to quit: '
    cont = promptUser(msg)
    if not cont:
        print('User ended test')
        return
    final_val = BTN.value()
    print(f'Pressed button value is: {final_val}')
    if default_val != final_val:
        print('Button test passed')
        return True
    else:
        print('Button test failed')
        return False
    
    
def encTest() -> bool:
    while True:
        enc_a = ENCA.value()
        enc_b = ENCB.value()
        print(enc_a, enc_b)
        time.sleep(0.1)
    return True
    

def main():
    btnTest()
    encTest()

if __name__ == main():
    main()