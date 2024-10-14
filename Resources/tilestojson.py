import os
import json
from PIL import Image

# ----------------------------- Configuration -----------------------------

# Directory containing the PNG images
IMAGE_DIR = 'img'  # Adjust if your images are in a different folder

# Output JSON filename
OUTPUT_JSON = 'images_with_edge_ids.json'

# Define the grid size (d x d)
GRID_SIZE = 2  # Change this to your desired grid size (e.g., 3 for 3x3)

# Define the color mapping for tile types
# Adjust these RGB tuples based on your actual tile colors
COLOR_MAPPING = {
    'grass': (76, 230, 0),      # Green
    'beach': (244, 255, 129),    # Yellow
    'water': (3, 169, 244),      # Blue
}

# Tolerance for color matching (to account for slight variations)
COLOR_TOLERANCE = 10

# Rotation angles
ROTATIONS = [0, 90, 180, 270]

# --------------------------------------------------------------------------

def color_match(pixel, target_color, tolerance=COLOR_TOLERANCE):
    """
    Check if a pixel matches the target color within the given tolerance.

    Args:
        pixel (tuple): (R, G, B)
        target_color (tuple): (R, G, B)
        tolerance (int): Tolerance for each color channel

    Returns:
        bool: True if matches, False otherwise
    """
    return all(abs(p - t) <= tolerance for p, t in zip(pixel, target_color))

def determine_tile_type(tile_image):
    """
    Determine the tile type based on the dominant color in the tile.

    Args:
        tile_image (PIL.Image): Image of the tile

    Returns:
        str: Tile type ('grass', 'beach', 'water') or 'unknown'
    """
    # Resize the tile to reduce computation
    small_tile = tile_image.resize((1,1))
    dominant_color = small_tile.getpixel((0,0))[:3]  # Ignore alpha if present

    for tile_type, color in COLOR_MAPPING.items():
        if color_match(dominant_color, color):
            return tile_type
    return 'unknown'

def rotate_tile_order(tiles, rotation, grid_size):
    """
    Rotate the list of tiles based on the rotation angle.

    Args:
        tiles (list): List of tile types in row-major order
        rotation (int): Rotation angle (0, 90, 180, 270)
        grid_size (int): Number of tiles per side (d)

    Returns:
        list: Rotated list of tile types in row-major order
    """
    num_rotations = rotation // 90
    rotated_tiles = tiles.copy()
    for _ in range(num_rotations):
        # Perform a 90-degree clockwise rotation
        rotated_tiles = rotate_90_clockwise(rotated_tiles, grid_size)
    return rotated_tiles

def rotate_90_clockwise(tiles, grid_size):
    """
    Rotate the tiles 90 degrees clockwise.

    Args:
        tiles (list): List of tile types in row-major order
        grid_size (int): Number of tiles per side (d)

    Returns:
        list: Rotated list of tile types in row-major order
    """
    rotated = [''] * (grid_size * grid_size)
    for row in range(grid_size):
        for col in range(grid_size):
            original_index = row * grid_size + col
            rotated_row = col
            rotated_col = grid_size - 1 - row
            rotated_index = rotated_row * grid_size + rotated_col
            rotated[rotated_index] = tiles[original_index]
    return rotated

def get_edges(tiles, grid_size):
    """
    Extract edge patterns from the list of tiles.

    Args:
        tiles (list): List of tile types in row-major order
        grid_size (int): Number of tiles per side (d)

    Returns:
        dict: Edge patterns with keys 'up', 'right', 'down', 'left'
              Each edge is a tuple of tile types
    """
    edges = {
        'up': tuple(tiles[0:grid_size]),
        'right': tuple(tiles[col * grid_size + grid_size -1] for col in range(grid_size)),
        'down': tuple(tiles[-grid_size:]),
        'left': tuple(tiles[col * grid_size] for col in range(grid_size)),
    }
    return edges

def main():
    # Initialize edge pattern to ID mapping
    edge_id_mapping = {}
    current_id = 0

    # Initialize final data structure
    final_data = {}

    # List all PNG images in the IMAGE_DIR
    image_files = [f for f in os.listdir(IMAGE_DIR) if f.lower().endswith('.png')]

    if not image_files:
        print(f"No PNG images found in directory '{IMAGE_DIR}'. Please check the path.")
        return

    for image_file in image_files:
        image_path = os.path.join(IMAGE_DIR, image_file)
        try:
            with Image.open(image_path) as img:
                # Ensure image is in RGB mode
                img = img.convert('RGB')

                width, height = img.size
                if width % GRID_SIZE != 0 or height % GRID_SIZE != 0:
                    print(f"Image '{image_file}' dimensions ({width}x{height}) are not divisible by GRID_SIZE ({GRID_SIZE}). Skipping.")
                    continue

                tile_width = width // GRID_SIZE
                tile_height = height // GRID_SIZE

                # Extract tiles in row-major order
                tiles = []
                for row in range(GRID_SIZE):
                    for col in range(GRID_SIZE):
                        left = col * tile_width
                        upper = row * tile_height
                        right = left + tile_width
                        lower = upper + tile_height
                        tile_img = img.crop((left, upper, right, lower))
                        tile_type = determine_tile_type(tile_img)
                        tiles.append(tile_type)

                if 'unknown' in tiles:
                    print(f"Image '{image_file}' contains unknown tile types. Skipping.")
                    continue

                # Generate all rotations
                flag = False
                for rotation in ROTATIONS:
                    rotated_tiles = rotate_tile_order(tiles, rotation, GRID_SIZE)
                    if rotated_tiles == tiles and rotation != 0:
                        continue
                    edges = get_edges(rotated_tiles, GRID_SIZE)

                    # Assign IDs to edges
                    edge_ids = {}
                    for direction, pattern in edges.items():
                        if pattern not in edge_id_mapping:
                            edge_id_mapping[pattern] = current_id
                            current_id += 1
                        edge_ids[direction] = edge_id_mapping[pattern]

                    # Create a unique key for each rotation
                    base_name = os.path.splitext(image_file)[0]
                    rotated_image_name = f"{base_name}_{int(rotation/90)}"

                    # Add to the final data
                    final_data[rotated_image_name] = {
                        "image": image_file,  # Original image filename
                        "rotation": rotation,
                        "id": {
                            "up": edge_ids['up'],
                            "right": edge_ids['right'],
                            "down": edge_ids['down'],
                            "left": edge_ids['left'],
                        },
                        "map": {"up": [], "down": [], "left":[], "right":[]}
                    }

        except Exception as e:
            print(f"Error processing image '{image_file}': {e}")
            continue

    # Output edge pattern to ID mapping (optional)
    print("\nEdge Pattern to ID Mapping:")
    for pattern, id_ in edge_id_mapping.items():
        print(f"{pattern}: {id_}")

    # Write final data to JSON
    with open(OUTPUT_JSON, 'w') as json_file:
        json.dump(final_data, json_file, indent=4)

    print(f"\nJSON data has been written to '{OUTPUT_JSON}'")

if __name__ == "__main__":
    main()