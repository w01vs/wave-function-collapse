import json

# Step 1: Load the JSON Data
with open('images_with_edge_ids.json', 'r') as file:
    data = json.load(file)

OUTPUT_JSON = "mapped_ids.json"

# Step 2: Create a dictionary to store the compatibility information
map = {}

# Step 3: Determine compatibility for each image
for image_name, image_data in data.items():
    
    # Get the current image's IDs
    current_ids = image_data['id']

    # Compare with other images to find compatible neighbors
    for other_image_name, other_image_data in data.items():
        if image_name == other_image_name:
            continue  # Skip comparing the image with itself
        
        other_ids = other_image_data['id']

        # Check if the current image's "right" matches the other's "left"
        if current_ids['right'] == other_ids['left']:
            image_data['map']['right'].append(other_image_name)
        
        # Check if the current image's "left" matches the other's "right"
        if current_ids['left'] == other_ids['right']:
            image_data['map']['left'].append(other_image_name)
        
        # Check if the current image's "up" matches the other's "down"
        if current_ids['up'] == other_ids['down']:
            image_data['map']['up'].append(other_image_name)
        
        # Check if the current image's "down" matches the other's "up"
        if current_ids['down'] == other_ids['up']:
            image_data['map']['down'].append(other_image_name)

# Step 4: Output the compatibility dictionary
with open(OUTPUT_JSON, 'w') as json_file:
        json.dump(data, json_file, indent=4)