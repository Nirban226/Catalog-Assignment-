#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <math.h>
#include <string.h>

typedef struct {
    long long int x;
    long long int y;
} Point;

// Custom function to convert from a given base to decimal
long long int convert_to_decimal(const char* value, int base) {
    long long int result = 0;
    int length = strlen(value);
    
    for (int i = 0; i < length; i++) {
        int digit;
        if (value[length - 1 - i] >= '0' && value[length - 1 - i] <= '9') {
            digit = value[length - 1 - i] - '0'; // Convert char to digit
        } else if (value[length - 1 - i] >= 'a' && value[length - 1 - i] <= 'f') {
            digit = value[length - 1 - i] - 'a' + 10; // Convert 'a' to 10, 'b' to 11, ..., 'f' to 15
        } else if (value[length - 1 - i] >= 'A' && value[length - 1 - i] <= 'F') {
            digit = value[length - 1 - i] - 'A' + 10; // Convert 'A' to 10, 'B' to 11, ..., 'F' to 15
        } else {
            fprintf(stderr, "Invalid digit %c for base %d\n", value[length - 1 - i], base);
            return -1; // Error condition
        }

        if (digit >= 0 && digit < base) {
            result += digit * pow(base, i); // Add to result
        } else {
            fprintf(stderr, "Invalid digit %c for base %d\n", value[length - 1 - i], base);
            return -1; // Error condition
        }
    }
    
    return result;
}

// Lagrange interpolation to find the constant term (c)
long long int lagrange_interpolation(Point points[], int k) {
    long long int c = 0;
    for (int i = 0; i < k; i++) {
        long long int term = points[i].y;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (-points[j].x);
                term /= (points[i].x - points[j].x);
            }
        }
        c += term;
    }
    return c;
}

int main() {
    struct json_object *parsed_json;
    struct json_object *keys;
    struct json_object *n;
    struct json_object *k;
    struct json_object *root;
    struct json_object *base;
    struct json_object *value;

    size_t num_points;
    int min_points;

    FILE *file = fopen("input.json", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *file_contents = (char*) malloc(file_size + 1);
    fread(file_contents, 1, file_size, file);
    fclose(file);
    file_contents[file_size] = '\0';

    parsed_json = json_tokener_parse(file_contents);
    free(file_contents);

    json_object_object_get_ex(parsed_json, "keys", &keys);
    json_object_object_get_ex(keys, "n", &n);
    json_object_object_get_ex(keys, "k", &k);

    num_points = json_object_get_int(n);
    min_points = json_object_get_int(k);

    Point points[min_points];
    int point_index = 0;

    for (int i = 1; i <= num_points && point_index < min_points; i++) {
        char key[4];
        snprintf(key, sizeof(key), "%d", i);

        if (json_object_object_get_ex(parsed_json, key, &root)) {
            json_object_object_get_ex(root, "base", &base);
            json_object_object_get_ex(root, "value", &value);

            int base_val = json_object_get_int(base);
            const char* value_str = json_object_get_string(value);
            long long int x = i; // x is the key index
            long long int y = convert_to_decimal(value_str, base_val); // Decode y value

            // Debugging prints to check values
            printf("Decoded Point: (%lld, %lld) from base %d value %s\n", x, y, base_val, value_str);

            points[point_index].x = x;
            points[point_index].y = y;
            point_index++;
        }
    }

    if (point_index < min_points) {
        fprintf(stderr, "Not enough points to solve.\n");
        json_object_put(parsed_json);
        return 1;
    }

    long long int c = lagrange_interpolation(points, min_points);
    printf("Constant term (c): %lld\n", c);

    json_object_put(parsed_json);
    return 0;
}
