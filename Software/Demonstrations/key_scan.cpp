// Array to map key coordinate to 
const unsigned short MENA_MAP[5][16] = {
    {/* MENA vals of row 0 keys */},
    {/* MENA vals of row 1 keys */},
    {/* MENA vals of row 2 keys */},
    {/* MENA vals of row 3 keys */},
    {/* MENA vals of row 4 keys */},
};

const unsigned short KEY_MASK = 0xff00;

const unsigned short CTRL = 0x8000;
const unsigned short ALT = 0x4000;
const unsigned short SHIFT = 0x2000;
const unsigned short WIN = 0x1000;

const unsigned short KEY = 0x00FF;

const unsigned int WIDTH = 16;
const unsigned int HEIGHT = 5;

void get_key_press() {
    unsigned int mena_val = 0;
    unsigned int key_press = 0;
    while (true) {
        // reset mena_val
        mena_val = 0;

        for (unsigned int col = 0; col < WIDTH; col++) {

            // Write HIGH to column <col> of scanning matrix
            gpio_write(col, HIGH);

            for (unsigned int row = 0; row < HEIGHT; row++) {

                // Check for key  press at (<row>, <col>)
                if (gpio_read(row, HIGH)) { 
                    
                    // Get associated MENA value
                    key_press = MENA_MAP[row][col];

                    // If non-special key is pressed, overwrite 
                    // (intended to handle multiple key press problem, but may not work)
                    if (is_non_special(key_press)) {
                        // Mask key values for overwrite
                        mena_val &= KEY_MASK; 
                    }

                    // Bitwise or to update mena_val
                    mena_val |= key_press;

                }
            }

            // Set output to LOW if necessary
            gpio_clear(col);

        }

        // If key(s) is/are pressed, send interrupt w/ MENA value

        if (mena_val != 0) {
            
            generate_interrupt(mena_val);
        }
    }
}