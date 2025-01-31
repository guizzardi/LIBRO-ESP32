from machine import Pin, I2C
import ssd1306

# se non è specificato si utilizza l'indirizzo 0x3C
i2c = I2C(sda=Pin(21), scl=Pin(22))
display = ssd1306.SSD1306_I2C(128, 32, i2c)

display.text('Ciao Mondo', 0, 0, 1)
display.show()
