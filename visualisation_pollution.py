import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os


file_path = 'Projectcorals-main/Code/CO2_terrain.csv'
if not os.path.exists(file_path):
    print(f"Le fichier n'existe pas : {file_path}")
else:
    data = pd.read_csv(file_path)

# Loading data from the file


# Reshaping the data into a 100x100 array
terrain = data.reshape((100, 100))

# Creating the plot
plt.figure(figsize=(8, 8))
im = plt.imshow(terrain, cmap='viridis', origin='lower', aspect='equal')

# Adding a color bar with a label
cbar = plt.colorbar(im)
cbar.set_label("concentration of C02 [ppm]", fontsize=12)

# Adding labels and a title
plt.title("C02 in atmosphere", fontsize=14)
plt.xlabel("X", fontsize=12)
plt.ylabel("Y", fontsize=12)

# Customizing the ticks
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

# Displaying the plot
plt.show()

