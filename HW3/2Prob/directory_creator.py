#!/usr/bin/python3

import os

# Define the directory structure and file contents
directory_structure = {
    "test_directory": {
        "file1.txt": "Line 1\nLine 2\nLine 3\n",
        "file2.txt": "Line 1\nLine 2\n",
        "file10.log": "Log Line 1\n",
        "subdir1": {
            "file3.txt": "Line 1\n",
            "file4.txt": "Line 1\nLine 2\n",
            "subsubdir1": {
                "file5.txt": "Line 1\nLine 2\nLine 3\nLine 4\n",
                "file6.txt": "Line 1\n",
            },
        },
        "subdir2": {
            "file7.txt": "Line 1\nLine 2\n",
            "file8.txt": "Line 1\n",
            "file9.log": "Log Line 1\nLog Line 2\n",
        },
    },
}

# Function to create directories and files
def create_structure(base_path, structure):
    for name, content in structure.items():
        path = os.path.join(base_path, name)
        if isinstance(content, dict):
            os.makedirs(path, exist_ok=True)
            create_structure(path, content)
        else:
            with open(path, 'w') as f:
                f.write(content)

# Create the directory structure
create_structure('.', directory_structure)

