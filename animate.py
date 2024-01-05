import json
import sys
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

def animate_particles(json_file_path, interval=300, save_as_mp4=False):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')

    # Load JSON data from file
    with open(json_file_path, 'r') as file:
        data = json.load(file)

    def update(frame):
        ax.clear()

        # Extract particle positions at the given frame
        particle_positions = data[frame]["Particles"]

        for particle_data in particle_positions:
            particle_id = particle_data["ParticleID"]
            position = particle_data["Position"]

            # Plot particle positions
            ax.scatter(
                position["X"], position["Y"], position["Z"],
                marker='o', label=f'Particle {particle_id}'
            )

        # Display elapsed time (assuming it's available in your JSON data)
        elapsed_time = data[frame]["Time"]
        ax.text2D(0.05, 0.95, f'Time: {elapsed_time:.3f} seconds', transform=ax.transAxes)

    ani = FuncAnimation(fig, update, frames=len(data), interval=interval, repeat=False)

    # Set up plot parameters
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.legend()

    if save_as_mp4:
        ani.save('particle_positions_from_json.mp4', writer='ffmpeg', fps=30)

    plt.show()
if __name__=="__main__":
    if len(sys.argv)!=4:
        print("Usage: python database.py <function_name> <json_data_path> <interval>")
        sys.exit(1)
    function_name, json_file_path, interval = sys.argv[1:]
    print(function_name)
    if function_name == "animate_particles":
        animate_particles(json_file_path, interval )
    else:
        print("Error: function \"animate_particles\" is not found.")