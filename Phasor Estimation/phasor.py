import matplotlib.pyplot as plt
import numpy as np
import serial

# Initialize serial connection
ser = serial.Serial('COM13', 115200)  # Full path to COM port

# Create the plot
fig, ax = plt.subplots()

# Initialize quiver objects for each phase
q1 = ax.quiver(0, 0, 0, 0, angles='xy', scale_units='xy', scale=1, color='r', label="Phase A")
q2 = ax.quiver(0, 0, 0, 0, angles='xy', scale_units='xy', scale=1, color='g', label="Phase B")
q3 = ax.quiver(0, 0, 0, 0, angles='xy', scale_units='xy', scale=1, color='b', label="Phase C")

# Set plot labels and title
ax.set_xlabel("X-axis")
ax.set_ylabel("Y-axis")
ax.set_title("Phasor Diagram")
ax.grid(True)
ax.axhline(0, color='black', linewidth=0.5)
ax.axvline(0, color='black', linewidth=0.5)
ax.set_aspect('equal', 'box')
ax.legend()

# Initialize lists to store data for each phase
data1 = []
data2 = []
data3 = []

# Function to update the plot
# Function to update the plot
def update_plot(q1, data1, angle_rad1, q2, data2, angle_rad2, q3, data3, angle_rad3):
    if data1 and data2 and data3:
        x1, y1 = data1[-1]
        x2, y2 = data2[-1]
        x3, y3 = data3[-1]
        q1.set_UVC(x1, y1)
        q2.set_UVC(x2, y2)
        q3.set_UVC(x3, y3)
        # Annotate with angle value
        angle_string = f"Angle A: {(angle_rad1):.2f}°, Angle B: {(angle_rad2):.2f}°, Angle C: {(angle_rad3):.2f}°"
        ax.legend([angle_string], loc='upper center')
        plt.draw()
        plt.pause(0.01)


# Read and process the data
while True:
    line = ser.readline().decode('utf-8').strip()
    print(line)
    parts = line.split(",")
    if len(parts) == 3:
        angle_rad1 = float(parts[0])
        angle_rad2 = float(parts[1])
        angle_rad3 = float(parts[2])
        
        # Calculate the x and y components for each phase
        x_component1 = np.cos(angle_rad1)
        y_component1 = np.sin(angle_rad1)
        
        x_component2 = np.cos(angle_rad2)
        y_component2 = np.sin(angle_rad2)
        
        x_component3 = np.cos(angle_rad3)
        y_component3 = np.sin(angle_rad3)
        
        # Update the data for each phase
        data1.append((x_component1, y_component1))
        data2.append((x_component2, y_component2))
        data3.append((x_component3, y_component3))
        
        # Update the plot
        update_plot(q1, data1, angle_rad1,q2, data2, angle_rad2,q3, data3, angle_rad3)
        # update_plot(q2, data2, angle_rad2)
        # update_plot(q3, data3, angle_rad3)
