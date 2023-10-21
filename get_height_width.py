from PIL import Image
from pathlib import Path

DATA = {
    "name" : "",
    "w&h":""
}
DATA_LIST = []
ENUM = "enum {{\n\t{nums}\n}};"
MATRIX = "int {name}[{len}][2] = {{\n\t{items}\n}};"
W_H_ENUM = "enum {\n\tWIDTH,\n\tHEIGHT\n};"
X_Y_ENUM = "enum {\n\tx,\n\ty\n};"
ARRAY = "const unsigned char* {name}[{len}] = {{\n\t{items}\n}};"
NAME = "SUB_MENU"
def walk(path): 
    for p in Path(path).iterdir(): 
        if p.is_dir(): 
            yield from walk(p)
            continue
        yield p.resolve()
        
def get_num_pixels(filepath):
    width, height = Image.open(filepath).size
    return "{" + str(width) + ", " + str(height) + "}"

for img in walk(Path("F:/Programme/rlcv3/images/sub_menu")): 
    temp_data = DATA.copy()
    w_h = get_num_pixels(img)
    temp_data["name"] = img.stem
    temp_data["w&h"] = w_h
    DATA_LIST.append(temp_data.copy())

output = []
name = "BITMAP_" + NAME + "_LEN "
length = len(DATA_LIST)
name_list = [data["name"] for data in DATA_LIST]
nums = ",\n\t".join(name_list)
output.append(ENUM.format(nums=nums))
output.append(W_H_ENUM)
output.append(X_Y_ENUM)
output.append("#define " + name + str(length))
w_h_list = [data["w&h"] for data in DATA_LIST]
items = ",\n\t".join(w_h_list)
output.append(MATRIX.format(name="W_H_MATRIX_" + NAME, len=name.strip(), items=items))
w_h_list = []
for i in range(length):
    w_h_list.append("{0, 0}")
    
items = ",\n\t".join(w_h_list)
output.append(MATRIX.format(name="X_Y_MATRIX_" + NAME, len=name.strip(), items=items))

bitmap_list = []
for entry in name_list:
    entry = "BITMAP_" + entry
    bitmap_list.append(entry)

items = ",\n\t".join(bitmap_list)
output.append(ARRAY.format(name="BITMAP_" + NAME + "_ARRAY", len=name.strip(), items = items))

with open("test.h", "w") as opened_file:
    output_str = "\n\n".join(output)
    opened_file.write(output_str)