//*********************************************************************************************

/* Serial port baudrate */
#define SERIAL_BAUDRATE (115200U)

/* Number of channels on the device */
#define NUM_CHANNELS (8U)

/* Macros to define logic levels for relay on state and relay off state */
#define RELAY_ON_STATE LOW
#define RELAY_OFF_STATE HIGH

/* Maximum number of bytes in the response message */
#define RESPONSE_MAX_BYTES (20U)

//*********************************************************************************************





//*********************************************************************************************

/* This array stores the digital output pins,
these pins will be used to control the relays*/
static u8 channel_map[NUM_CHANNELS] = {
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9
};

/* Array to hold channel states */
static u8 channel_state[NUM_CHANNELS];

//*********************************************************************************************





void setup() {

  /* Initialize the serial port*/
  Serial.begin( SERIAL_BAUDRATE );

  /* Configure the pin mode */
  for( u8 channel=0; channel<NUM_CHANNELS; channel++ ) {
    pinMode( channel_map[channel], OUTPUT );
    digitalWrite( channel_map[channel], RELAY_OFF_STATE );
    channel_state[ channel ] = (u8) 0x00U;
  }

}

u8 in, ch;
void loop()
{
        if( Serial.available() >= 1 ) {
                in = Serial.read();
                ch = (in & (0xF));

                if( ch == 0xF ) {
                        Serial.write( 0xA5 );
                }
                else if( ch < 8 ) {
                        /* check the requested state */
                        if( (in & 0xF0) ) {
                                digitalWrite( channel_map[ ch ], RELAY_ON_STATE );
                        } else {
                                digitalWrite( channel_map[ ch ], RELAY_OFF_STATE );
                        }

                        Serial.write( 0xA5 );

                        /* Delay for relay switching */
                        delay(1);
                }
                else {
                        Serial.write( 0x5A );
                }
        }
}
