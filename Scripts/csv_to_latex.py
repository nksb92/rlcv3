import csv
import os

def escape_latex(text):
    """Escapes special characters for LaTeX."""
    if not text:
        return ""
    # Define replacements for special LaTeX characters
    replacements = {
        '&': r'\&',
        '%': r'\%',
        '$': r'\$',
        '#': r'\#',
        '_': r'\_',
        '{': r'\{',
        '}': r'\}',
        '~': r'\textasciitilde{}',
        '^': r'\^{}',
    }
    
    # Handle backslash separately first
    text = text.replace('\\', r'\textbackslash{}')
    
    for char, replacement in replacements.items():
        text = text.replace(char, replacement)
    return text

def convert_csv_to_latex(input_file, output_file):
    try:
        with open(input_file, mode='r', encoding='utf-8') as f:
            reader = csv.reader(f)
            rows = list(reader)
    except FileNotFoundError:
        print(f"Error: File {input_file} not found.")
        return

    if not rows:
        print("Error: CSV file is empty.")
        return

    # Limit to first 10 columns
    num_columns = 10
    headers = rows[0][:num_columns]
    data = [row[:num_columns] for row in rows[1:]]

    # Find the index of the 'Link' column
    link_col_index = -1
    for i, h in enumerate(headers):
        if "link" == h.lower().strip():
            link_col_index = i
            break

    latex_lines = []
    latex_lines.append(r'\begin{table}[H]')
    latex_lines.append(r'\centering')
    latex_lines.append(r'\resizebox{\textwidth}{!}{%')
    latex_lines.append(r'\begin{tabular}{|' + 'l|' * num_columns + '}')
    latex_lines.append(r'\hline')

    # Header
    latex_lines.append(' & '.join(r'\textbf{' + escape_latex(h) + '}' for h in headers) + r' \\ \hline')

    # Data rows
    for row in data:
        # Ensure row has enough columns (pad with empty strings if needed)
        row += [''] * (num_columns - len(row))
        
        formatted_cells = []
        for i, cell in enumerate(row):
            escaped_text = escape_latex(cell)
            if i == link_col_index and cell.strip():
                formatted_cells.append(r'\href{' + escaped_text + r'}{View}')
            else:
                formatted_cells.append(escaped_text)
        
        latex_lines.append(' & '.join(formatted_cells) + r' \\ \hline')

    latex_lines.append(r'\end{tabular}')
    latex_lines.append(r'}')
    latex_lines.append(r'\caption{Bill of Materials}')
    latex_lines.append(r'\label{tab:bom}')
    latex_lines.append(r'\end{table}')

    with open(output_file, mode='w', encoding='utf-8') as f:
        f.write('\n'.join(latex_lines))
    print(f"LaTeX table generated at: {output_file}")

if __name__ == "__main__":
    input_path = r"filename.csv"
    output_path = r"bom_table.tex"
    convert_csv_to_latex(input_path, output_path)