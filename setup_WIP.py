import tkinter as tk
from tkinter import ttk

_enableGPIO = False
_enableUART2 = False

def setBaudRate(baudrate):
    data = []
    with open("STM/Inc/Utils/UART.h", 'r', encoding='UTF-8') as UART_file:
        data = UART_file.readlines()
        baudrate_line = data.index("//BAUDRATE\n") + 1
        data[baudrate_line] = f"#define BAUDRATE {baudrate}\n"
    with open("STM/Inc/Utils/UART.h", 'w', encoding='UTF-8') as UART_file:
        UART_file.writelines(data)

def generate(window):
    setBaudRate(9600)

if __name__ == "__main__":
    window = tk.Tk()
    window.geometry('600x300')

    GPIO = ttk.Checkbutton(
        window,
        text = "Enable UART"
    )

    generateButton = tk.Button(window, text = "Generate", command = lambda: generate(window))
    generateButton.pack()
    window.mainloop()