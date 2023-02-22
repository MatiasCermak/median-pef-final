import numpy as np
from PIL import Image

# Load the BMP image
img = Image.open("forest.bmp")

# Convert the image to a numpy array
img_arr = np.array(img)

# Define the probability of the salt and pepper noise
noise_prob = 0.25

# Add salt and pepper noise to the image
for i in range(img_arr.shape[0]):
    for j in range(img_arr.shape[1]):
        if np.random.random() < noise_prob:
            if np.random.random() < 0.5:
                img_arr[i][j] = 0
            else:
                img_arr[i][j] = 255

# Convert the numpy array back to an image
noisy_img = Image.fromarray(img_arr)

# Save the noisy image
noisy_img.save("forest-noise-extreme.bmp")