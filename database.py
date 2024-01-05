import sys
import json
import psycopg2

def load_postgresql_config(config_file):
    # Load PostgreSQL configuration from the file
    #print(config_file)
    with open(config_file, "r") as file:
        config = json.load(file)
    return config

def send_data_to_db(table_name, config, json_data):
    # Connect to PostgreSQL using the configuration
    connection = psycopg2.connect(
        host=config["host"],
        port=config["port"],
        database=config["database_name"],
        user=config["user"],
        password=config["password"]
    )

    # Create a cursor
    cursor = connection.cursor()

    # Create the table if it doesn't exist
    cursor.execute(f'''
        CREATE TABLE IF NOT EXISTS {table_name} (
            data jsonb
        );
    ''')

    # Insert JSON data into PostgreSQL
    cursor.execute(f'''
        INSERT INTO {table_name} (data)
        VALUES (%s);
    ''', (json.dumps(json_data),))

    # Commit changes
    connection.commit()

    print("Data has been sent to the database.")
    # Close the connection
    cursor.close()
    connection.close()

def retrieve_and_save_to_json(table_name, config, json_data_path):
    # Connect to PostgreSQL using the configuration
    connection = psycopg2.connect(
        host=config["host"],
        port=config["port"],
        database=config["database_name"],
        user=config["user"],
        password=config["password"]
    )

    # Create a cursor
    cursor = connection.cursor()

    # Retrieve data from PostgreSQL
    cursor.execute(f'''
        SELECT data FROM {table_name};
    ''')

    # Fetch the first row
    row = cursor.fetchone()

    if row:
        # Extract the specific element (data[0][0]) from the first row
        specific_data = row[0]

        # Save the specific data as JSON
        with open(json_data_path, 'w') as json_file:
            json.dump(specific_data, json_file)

        print(f"Specific data has been retrieved and saved to {json_data_path}.")
    else:
        print("No data retrieved.")

    # Close the connection
    cursor.close()
    connection.close()
if __name__ == "__main__":
    # Check if the correct number of arguments is provided
    #print(sys.argv)
    if len(sys.argv) != 5:
        print("Usage: python database.py <function_name> <table_name> <config_file> <json_data_path> or python database.py <function_name> <json_data_path>")
        sys.exit(1)
    # Extract arguments
    function_name, table_name, config_file, json_data_path = sys.argv[1:]
    #print(function_name, table_name, config_file, json_data_path)
    # Load PostgreSQL connection details from a file
    config = load_postgresql_config(config_file)["postgresql"]

    # Call the specified function
    if function_name == "send_data_to_db" :
        # Load the JSON data from a file
        with open(json_data_path, "r") as file:
            json_data = json.load(file)
        send_data_to_db(table_name, config, json_data)
    elif function_name == "retrieve_and_save_to_json":
        retrieve_and_save_to_json(table_name, config, json_data_path)
    else:
        print(f"Error: Unknown function name '{function_name}'")
        sys.exit(1)