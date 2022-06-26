import re
import string

FILENAME = 'inputFile.txt'

def readFile(fileName):
    lines = None

    with open(fileName) as file:
        lines = file.readlines()

    return lines
    

#calls readFile to get all items and stores them in a list
#   uses .strip() to remove newLine charactor
def getInventory():
    inventory = {}

    text = readFile(FILENAME)

    for line in text:
        line = line.strip()
        words = line.split(" ")

        for word in words:
            if word in inventory:
                inventory[word] = inventory[word] + 1
            else:
                inventory[word] = 1
    return inventory 


#calls getInventory to show how many times each item is called within the list
def determineInventory():
    inventory = {}
    inventory = getInventory()

    for key in list(inventory.keys()):
         print(key , ' : ' , inventory[key])

# lists all items along with a character to indicate the number of times an item is listed.
def histogram(item):
    inventory = {}
    inventory = getInventory()
    max = 0

    for key in list(inventory.keys()):
        if max < len(key):
            max = len(key)
    
    for key in list(inventory.keys()):
        space = max - len(key) + 4
        print(key , (' : ').ljust(space, '-') , (inventory[key] * item))

    return 0
# will provide number of items for specified item
def determineFrequency(item):
    inventory = getInventory()
    if item in inventory.keys():
        return inventory[item]
    else:
        return 0
    

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v
