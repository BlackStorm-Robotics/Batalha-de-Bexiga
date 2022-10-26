from inputs import get_gamepad
import serial

# Abre a porta serial (bluetooth) para envio dos comandos.
bt_port = input("Bluetooth Serial Port (COM...): ")
if bt_port == " " or not bt_port:
    bt_port = "COM11" #default
print("Conectando com a porta " + bt_port)
print("Carregando...")
s = serial.Serial(bt_port)

lastMsg: bytes = '0'
nextMsg: bytes = '0'
x: int = 0
y: int = 0
arrow_x: int = 0
arrow_y: int = 0

# O update é chamado quando há mudança de estado no analógico ou nas setinhas. Faz a interpretação dos comandos.
# 0 = Stop, 1 = Go Forward, 2 = Go Backward, 3 = Rotate Right, 4 = Rotate Left, 5 = Turn Right Forward, 6 = Turn Left Forward, 7 = Turn Right Backward, 8 = turn Left Backward
def update():
    global lastMsg, nextMsg, x, y
    up = y > 13000 or arrow_y == -1
    down = y < -13000 or arrow_y == 1
    right = x > 18000 or arrow_x == 1
    left = x < -18000 or arrow_x == -1
    if up and right:
        nextMsg = b'5'
    elif up and left:
        nextMsg = b'6'
    elif down and right:
        nextMsg = b'7'
    elif down and left:
        nextMsg = b'8'
    elif up:
        nextMsg = b'1'
    elif down:
        nextMsg = b'2'
    elif right:
        nextMsg = b'3'
    elif left:
        nextMsg = b'4'
    else:
        nextMsg = b'0'

    # Só envia mensagem por bluetooth caso a mensagem tenha mudado.
    if nextMsg != lastMsg:
        lastMsg = nextMsg
        send(nextMsg)

# Envia o código para o robô via Bluetooth.
def send(msg: bytes):
    s.write(msg)
    #print(msg)

# Faz a mágica acontecer :D
print("O controle está ativo")
while 1:
    events = get_gamepad()
    for event in events:
        if event.code == 'ABS_X':
            x = event.state
            update()
        if event.code == 'ABS_Y':
            y = event.state
            update()
        if event.code == 'ABS_HAT0X':
            arrow_x = event.state
            update()
        if event.code == 'ABS_HAT0Y':
            arrow_y = event.state
            update()

# Fecha a conexão serial.
s.close()
print("Porta serial fechada")
print("Programa encerrado.")