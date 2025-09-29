#!/bin/bash

# Update package list and install necessary dependencies
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    sudo apt-get update
    sudo apt-get install -y build-essential cmake g++ 

    # Additional dependencies can be added here
    echo "Dependencies installed successfully for Linux."
else
    echo "This script is intended for Linux systems only."
fi