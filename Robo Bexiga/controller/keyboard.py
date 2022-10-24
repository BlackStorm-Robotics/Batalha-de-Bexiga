import tkinter
import serial

# Lista das possíveis teclas de input com a informação se estão ou não pressionadas.
pressed = {
    'Up': False,
    'Down': False,
    'Right': False,
    'Left': False,
    'w': False,
    's': False,
    'd': False,
    'a': False
}
entry_keys = pressed.keys()

# Abre a porta serial (bluetooth) para envio dos comandos.
bt_port = input("Bluetooth Serial Port (COM...): ")
if bt_port == " " or not bt_port:
    bt_port = "COM11" #default
print("Conectando com a porta " + bt_port)
print("Carregando...")
s = serial.Serial(bt_port)

# É chamada sempre que uma tecla é pressionada / está sendo pressionada.
def press_handler(event):
    if event.keysym in entry_keys:
        if not pressed[event.keysym]:
            pressed[event.keysym] = True
            #print(event.keysym + ' pressed')
            update()

# É chamada sempre que uma tecla que estava sendo pressionada é solta.
def release_handler(event):
    if event:
        if event.keysym in entry_keys:
            pressed[event.keysym] = False
            #print(event.keysym + ' released')
            update()

# O update é chamado quando há mudança de estado. Faz a interpretação dos comandos.
# 0 = Stop, 1 = Go Forward, 2 = Go Backward, 3 = Rotate Right, 4 = Rotate Left, 5 = Turn Right Forward, 6 = Turn Left Forward, 7 = Turn Right Backward, 8 = turn Left Backward
def update():
    up = pressed['Up'] or pressed['w']
    down = pressed['Down'] or pressed['s']
    right = pressed['Right'] or pressed['d']
    left = pressed['Left'] or pressed['a']
    if up and right:
        send(b'5')
    elif up and left:
        send(b'6')
    elif down and right:
        send(b'7')
    elif down and left:
        send(b'8')
    elif up:
        send(b'1')
    elif down:
        send(b'2')
    elif right:
        send(b'3')
    elif left:
        send(b'4')
    else:
        send(b'0')

# Envia o código para o robô via Bluetooth.
def send(msg: bytes):
    s.write(msg)
    #print(msg)

# Cria uma janela no sistema operacional para receber o input do teclado.
r = tkinter.Tk()
r.title("Blackstorm")
r.geometry('400x200')
label = tkinter.Label(r, text = "ROBÔ BEXIGA\nControle do robô\nAtivo")
label.pack()

# Cadastra os eventos de tecla pressionada e solta.
r.bind('<KeyPress>', press_handler)
r.bind('<KeyRelease>', release_handler)

# Faz a mágica acontecer :D
print("O controle está ativo")
r.mainloop()

# Fecha a conexão serial.
s.close()
print("Porta serial fechada")
print("Programa encerrado.")
