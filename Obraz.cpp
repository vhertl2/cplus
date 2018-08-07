#include "stdafx.h"
#include "Obraz.h"

/*
Obraz::Obraz()
{
}
*/
Obraz::Obraz(const char *filename) {
	CImg<int> src(filename); //nacte obrazek ze souboru
	pictureName = filename;
	width = src.width(); //vypise vysku obrazku v pixelech
	height = src.height(); //vypise sirku obrazku v pixelech
	pi = new int*[width]; //dynamicka alokace 2D pole
	for (int i = 0; i < width; i++) {
		pi[i] = new int[height];
	}
#ifdef DEBUG
	cout << "Sirka obrazku je: " << width << endl; // vypise sirku a vysku obrazku na konzoli
	cout << "Vyska obrazku je: " << height << endl;
#endif // DEBUG
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int R = (int)src(x, y, 0, 0); // separuje cerveny kanal z obrazku
			int G = (int)src(x, y, 0, 1);
			int B = (int)src(x, y, 0, 2);
			pi[x][y] = (int)(0.33*R + 0.33*G + 0.33*B); // aritmetickym proumerovanim hodnot pixelu dostaneme grayscale
		}
	}
	//src.display("source");
};

Obraz::Obraz(int width, int height) {

	this->width = width;
	this->height = height;
	pi = new int*[width]; //dynamicka alokace 2D pole
	for (int i = 0; i < width; i++) {
		pi[i] = new int[height];
	}
#ifdef DEBUG
	cout << "Sirka obrazku je: " << width << endl; // vypise sirku a vysku obrazku na konzoli
	cout << "Vyska obrazku je: " << height << endl;
#endif
}

Obraz::Obraz(Obraz &x, Kernel &K) {
	this->width = x.width;
	this->height = x.height;
	kernelName = K.getKernelName();
	x.pictureName = kernelName;

	pi = new int*[width]; //dynamicka alokace 2D pole
	for (int i = 0; i < width; i++) {
		pi[i] = new int[height];
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pi[i][j] = x.pi[i][j];
		}
	}

	kw = K.getKernelWidth();
	kh = K.getKernelHeight();
#ifdef DEBUG
	cout << "Sirka jadra je: " << kw << endl; // vypise sirku a vysku obrazku na konzoli
	cout << "Vyska jadra je: " << kh << endl;
#endif

	k = new double*[kw]; //dynamicka alokace 2D pole
	for (int i = 0; i < kw; i++) {
		k[i] = new double[kh];
	}

	for (int i = 0; i < kw; i++) {
		for (int j = 0; j < kh; j++) {
			k[i][j] = K[i][j];
		}
	}
	for (int i = 0; i < kw; i++) {
		for (int j = 0; j < kh; j++) {
		}
	}
	x = convolution(x);

	if (k != NULL) {
		for (int i = 0; i < kw; i++)
			delete[] k[i];
		delete[] k;
	}

}

Obraz::Obraz(Obraz &x) {
	pi = new int*[width = x.width];
	for (int i = 0; i < width; i++) {
		pi[i] = new int[height = x.height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pi[i][j] = x.pi[i][j];
		}
	}
}

int Obraz::getWidth() {
	return width;
}

int Obraz::getHeight() {
	return height;
}

void Obraz::show() {
	CImg<int> img; // vytvori prazdny obrazek pomoci CImg
	img.assign(width, height, 1, 1);  // vytvorenemu obrazku img priradi sirku a vysku, 1 - obrazek nema 3. dimenzi a 1 - obrazek pouziva pouze jeden kanal
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			img(x, y, 0) = (const int)pi[x][y]; // priradi hodnotu z dynamického pole intenzit na pozici x,y
												//img(x, y, 1) = (const int)pi[x][y];
												//img(x, y, 2) = (const int)pi[x][y];
		}
	}
	img.display(pictureName);
}

void Obraz::printIntensities() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			cout << pi[i][j] << ", ";
		}
		cout << endl;
	}
}

Obraz Obraz::threshold(int t) {
	if (t < 0 || 255 < t) throw Vyjimka(4);
	Obraz ThresholdedImage(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (pi[i][j] >= t) {
				ThresholdedImage.pi[i][j] = pi[i][j];
			}
			else {
				ThresholdedImage.pi[i][j] = 0;
			}
		}
	}
	return ThresholdedImage;
}
Obraz Obraz::bwimage(int t) {
	if (t < 0 || 255 < t) throw Vyjimka(4);
	Obraz bwImage(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (pi[i][j] >= t) {
				bwImage.pi[i][j] = 255;
			}
			else {
				bwImage.pi[i][j] = 0;
			}
		}
	}
	return bwImage;
}

Obraz Obraz::convolution(Obraz &x) {
	double acumulator;
	Obraz convImage(x.width - (2 * (kw / 2)), x.height - (2 * (kh / 2)));
	for (int i = kw / 2; i < width - kw / 2; i++) {
		for (int j = kh / 2; j < height - kh / 2; j++) {
			acumulator = 0;
			for (int ki = -kw / 2; ki < kw / 2 + 1; ki++) {
				for (int kj = -kh / 2; kj < kh / 2 + 1; kj++) {
					acumulator += (double)pi[i + ki][j + kj] * k[ki + kw / 2][kj + kh / 2];
				}
			}
			convImage.pi[i - kw / 2][j - kh / 2] = (int)acumulator;
		}
	}
	return convImage;
}

Obraz Obraz::operator-() { //operator pro inverzi obrazu
	Obraz InvertedImg(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			InvertedImg.pi[i][j] = 255 - pi[i][j]; // vrati na mista pixelu inverzni hodnoty
		}
	}
	InvertedImg.pictureName = "Inverted image";
	return InvertedImg;
}

Obraz Obraz::operator()(int x1, int y1, int x2, int y2) {
	if (width < x1 || x1 < 0 || height < y1 || y1 < 0 || width < x2 || x2 < 0 || height < y2 || y2 < 0) throw Vyjimka(1);
	if (x2 < x1 || y2 < y1) throw Vyjimka(2);
	Obraz CutImage((x2 - x1), (y2 - y1));
	for (int i = x1; i < x2; i++) {
		for (int j = y1; j < y2; j++) {
			CutImage.pi[i - x1][j - y1] = pi[i][j];
		}
	}
	return CutImage;
}

Obraz Obraz::operator=(const Obraz &x) {
	if (pi != NULL) {
		for (int i = 0; i < width; i++)
			delete[] pi[i];
		delete[] pi;
	}
	pi = new int*[width = x.width];
	for (int i = 0; i < width; i++) {
		pi[i] = new int[height = x.height];
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pi[i][j] = x.pi[i][j];
		}
	}
	return *this;
}

int* Obraz::operator[](int i) const {
	if (width < i || i < 0 ) throw Vyjimka(3);
	return pi[i];
}


Obraz::~Obraz()
{
	for (int i = 0; i < width; i++)
		delete[] pi[i];
	delete[] pi;
}
