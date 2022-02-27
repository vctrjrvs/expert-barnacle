import re
import string
from collections import Counter

def printsomething():
    print("Hello from Victor, this is my Corner Grocer Project!")

#def PrintMe(v):
#    print("You sent me: " + v)
#    return 100;

#def SquareValue(v):
#    return v * v


def readFile():
    #open up and read our file, split it, and sort it
    dataFile = open("DataTemp.txt")
    productFile = dataFile.read().split()
    sortedProduct = sorted(set(productFile))

    #loop through and print as sorted
    for product in sortedProduct:
        print("******************************")
        print(product, " : ", productFile.count(product))
        print("******************************")
    dataFile.close() #close for memory sake

def totalProducts(el):
    #open, read, and sort once again
    dataFile = open("DataTemp.txt")
    productFile = dataFile.read().split()
    sortedProduct = sorted(set(productFile))
    dataFile.close()

    total = 0
    inventory = 0
    totalCount = 0

    #count each product in the list
    for product in sortedProduct:
        totalCount += 1
    
    #add frequencies
    for product in sortedProduct:
        tempProduct = product
        inventory += 1
        if (tempProduct == el):
            total = productFile.count(product)
            inventory -= 1
        if (tempProduct != el and inventory == totalCount):
            return -1

    return total

def readWriteFile():
    #open and read info to be written to a frequency file
    dataFile = open("DataTemp.txt")
    frequencyData = open("frequency.dat", "w")
    productFile = dataFile.read().split()
    sortedProduct = sorted(set(productFile))

    for product in sortedProduct:
        frequencyData.write(product)
        frequencyData.write(" ")
        frequencyData.write(str(productFile.count(product)))
        frequencyData.write("\n")
    frequencyData.close()

    #read our data file to create the histogram
    histogramData = open("frequency.dat", "r")
    histogramProductsData = histogramData.readlines()
    #temporary varibles to help set up loops
    tempFreq = 0
    tempProd = ""
    #loops to help us set up our histogram
    for data in histogramProductsData:
        tempInt = 0
        tempString = data.split()
        for product in tempString:
            tempInt += 1
            if (tempInt == 1):
                tempProd = product
                print(tempProd, end = " ")
            if (tempInt >= 2):
                tempFreq = int(product)
        #print out our histogram
        for i in range(tempFreq):
                print("*", end = "")
        print("\n")
        #print("******************************")
        #print("\n")