#include <Adafruit_NeoPixel.h>

#define PIN 6

#define BRIGHTNESS 50

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
	delay(250);
}

void loop() {
	// Some example procedures showing how to display to the pixels:
	//colorWipe(strip.Color(255, 0, 0), 50); // Red
	//flashColor(strip.Color(255, 0, 0), 20,20); // Red

	//fadeColor(strip.Color(16,0,0),10, 3);

	//colorWipe(strip.Color(0, 255, 0), 50); // Green
	//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
	//  // Send a theater pixel chase in...
	//  theaterChase(strip.Color(127, 127, 127), 50); // White
	//theaterChase(strip.Color(127,   0,   0), 50); // Red
	//theaterChase(strip.Color(  0,   0, 127), 50); // Blue

	//rainbow(20);
	//rainbowCycle(20);
	//theaterChaseRainbow(50);

	//swapHalf(strip.Color(16,0,0),72, 200, 64, 10);
	//flashPixels(strip.Color(255,0,0), strip.Color(32,0,0), 0, 10, 5, 20);

	//flashPixels(strip.Color(255,0,0), strip.Color(32,0,0), 40, 60, 5, 20);

	//flashPixels(strip.Color(255,0,0), strip.Color(32,0,0), 130, 60, 5, 20);

	uint16_t blocks[][2] = {
		{ 0,10 },
		{ 40,60 },
		{ 130,14 }
	};

	flashBlocks(strip.Color(255, 0, 0), strip.Color(32, 0, 0), blocks, 3, 5, 20);

	/* setStripSet(strip.Color(255,0,0),40,60);
	strip.show();
	delay(20);
	setStripSet(strip.Color(0,0,0),40,60);
	strip.show();
	delay(20);
	setStripSet(strip.Color(255,0,0),40,60);
	strip.show();
	delay(20);
	setStripSet(strip.Color(0,0,0),40,60);
	strip.show();
	delay(20);
	setStripSet(strip.Color(255,0,0),40,60);
	strip.show();
	delay(20);
	setStripSet(strip.Color(0,0,0),40,60);
	strip.show();
	delay(20);
	setStripSet(strip.Color(32,0,0),40,60);
	strip.show();
	delay(200);
	*/
	delay(200);
	colorWipe(0, 0);
	setStripSet(strip.Color(0, 32, 0), 0, 40);
	setStripSet(strip.Color(32, 32, 0), 100, 44);
	strip.show();
	delay(1000);
	colorWipe(0, 0);

}

void flashBlocks(uint32_t flashColor, uint32_t endColor, uint16_t(*pixelBlocks)[2], uint8_t numBlocks, uint8_t flashCount, uint8_t flashDelay)
{
	// loop for the flash count
	for (uint8_t flashCounter = 0; flashCounter < flashCount; flashCounter++)
	{
		// set the color for the blocks
		for (uint16_t blockCounter = 0; blockCounter < numBlocks; blockCounter++)
		{
			setStripSet(flashColor, pixelBlocks[blockCounter][0], pixelBlocks[blockCounter][1]);
		}
		strip.show();
		delay(flashDelay);
		// blank the blocks out.
		for (uint16_t blockCounter = 0; blockCounter < numBlocks; blockCounter++)
		{
			setStripSet(strip.Color(0, 0, 0), pixelBlocks[blockCounter][0], pixelBlocks[blockCounter][1]);
		}
		strip.show();
		delay(flashDelay);
	}
	// set final color
	for (uint8_t blockCounter = 0; blockCounter < numBlocks; blockCounter++)
	{
		setStripSet(endColor, pixelBlocks[blockCounter][0], pixelBlocks[blockCounter][1]);
	}
	strip.show();
}

void flashPixels(uint32_t flashColor, uint32_t endColor, uint16_t startPixel, uint16_t pixelCount, uint8_t flashCount, uint8_t flashDelay) {
	// loop
	//    setPixel
	//    show
	//    delay
	//    setpixel (color=0)
	//  end loop
	for (uint8_t flashCounter = 0; flashCounter < flashCount; flashCounter++)
	{
		setStripSet(flashColor, startPixel, pixelCount);
		delay(flashDelay);
		strip.show();
		setStripSet(strip.Color(0, 0, 0), startPixel, pixelCount);
		delay(flashDelay);
		strip.show();
	}

	// setPixel
	setStripSet(endColor, startPixel, pixelCount);
	strip.show();
}

// fades color in and out.
void fadeColor(uint32_t color, uint8_t fadeDelay, uint8_t cycleCount)
{
	colorWipe(0, 0); // turn off all pixels

	for (uint8_t counter = 0; counter < cycleCount; cycleCount++)
	{
		for (uint8_t i = 0; i < 64; i++)
		{
			colorWipe(strip.Color(i, 0, 0), 0); // Red
			delay(fadeDelay);
			strip.show();
		}
		for (uint8_t i = 64; i > 0; i--)
		{
			colorWipe(strip.Color(i, 0, 0), 0); // Red
			delay(fadeDelay);
			strip.show();
		}
	}
}

void setStripSet(uint32_t color, uint16_t startPixel, uint16_t pixelCount)
{
	//TODO: safety bounds for startPixel, and (StartPixel + pixelCount)

	for (uint8_t pixNum = startPixel; pixNum < (startPixel + pixelCount); pixNum++)
	{
		strip.setPixelColor(pixNum, color);
	}
}

void swapHalf(uint32_t color, uint8_t splitPoint, uint8_t swapDelay, uint8_t brightness, uint8_t cycleCount)
{
	for (uint8_t counter = 0; counter < cycleCount; cycleCount++)
	{

		for (uint8_t i = 0; i < strip.numPixels(); i++)
		{
			if (i < splitPoint)
			{
				strip.setPixelColor(i, color);
			}
			else
			{
				strip.setPixelColor(i, 0);
			}
			//colorWipe(strip.Color(brightness, 0, 0), 0); // Red
		}
		strip.show();

		delay(swapDelay);

		for (uint8_t i = 0; i < strip.numPixels(); i++)
		{
			if (i < splitPoint)
			{
				strip.setPixelColor(i, 0);
			}
			else
			{
				strip.setPixelColor(i, color);
			}
			//colorWipe(strip.Color(brightness, 0, 0), 0); // Red
		}
		strip.show();
		delay(swapDelay);
	}
}

void flashColor(uint32_t color, uint8_t wait, uint8_t count)
{
	for (uint8_t i = 0; i < count; i++)
	{
		colorWipe(color, 0); // set pixels to specified color
		strip.show();
		delay(wait);
		colorWipe(0, 0); // turn off all pixels
		strip.show();
		delay(wait);
	}

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		//strip.show();
		delay(wait);
	}
}

void rainbow(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256; j++) {
		for (i = 0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel((i + j) & 255));
		}
		strip.show();
		delay(wait);
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
		for (i = 0; i< strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
		}
		strip.show();
		delay(wait);
	}
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
	for (int j = 0; j<10; j++) {  //do 10 cycles of chasing
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, c);    //turn every third pixel on
			}
			strip.show();

			delay(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
	}
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
	for (int j = 0; j < 256; j++) {     // cycle all 256 colors in the wheel
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, Wheel((i + j) % 255));    //turn every third pixel on
			}
			strip.show();

			delay(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	else {
		WheelPos -= 170;
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
}
