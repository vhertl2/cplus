#include "stdafx.h"
#include "Kernel.h"

Kernel::Kernel(int kernelType) {
	kt = kernelType;
	switch (kt) {
	case 1: {
		kw = 3;
		kh = 3;
		kernelName = "Identity";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[5][5] = { //identita
			0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0,
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}
	case 2: {
		kw = 3;
		kh = 3;
		kernelName = "Edge detection 1";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[3][3] = { //detekce hran 1
			1.0, 0.0, -1.0,
			0.0, 0.0, 0.0,
			-1.0, 0.0, 1.0,
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}
	case 3: {
		kw = 3;
		kh = 3;
		kernelName = "Edge detection 2";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[3][3] = { // detekce hran 2
			0.0, 1.0, 0.0,
			1.0, -4.0, 1.0,
			0.0, 1.0, 0.0,
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}case 4: {
		kw = 3;
		kh = 3;
		kernelName = "Edge detection 3";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[3][3] = { // detekce hran 3
			-1.0, -1.0, -1.0,
			-1.0, 8.0, -1.0,
			-1.0, -1.0, -1.0,
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}
	case 5: {
		kw = 3;
		kh = 3;
		kernelName = "Sharpen";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[3][3] = { // zaostøit
			0.0, -1.0, 0.0,
			-1.0, 5.0, -1.0,
			0.0, -1.0, 0.0,
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}

	case 6: {
		kw = 5;
		kh = 5;
		kernelName = "Gaussian Blur";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[5][5] = {
			1.0, 4.0, 6.0, 4.0, 1.0,
			4.0, 16.0, 24.0, 16.0, 4.0,
			6.0, 24.0, 36.0, 24.0, 6.0,
			4.0, 16.0, 24.0, 16.0, 4.0,
			1.0, 4.0, 6.0, 4.0, 1.0
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}
	case 7: {
		kw = 5;
		kh = 5;
		kernelName = "Box Blur";
		ker = new double*[kw]; //dynamicka alokace 2D pole
		for (int i = 0; i < kw; i++) {
			ker[i] = new double[kh];
		}
		double kernel[5][5] = { // krabicové rozmazání
			1.0, 1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0, 1.0,
			1.0, 1.0, 1.0, 1.0, 1.0,
		};
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				normFac += kernel[i][j];
			}
		}
		for (int i = 0; i < kw; i++) {
			for (int j = 0; j < kh; j++) {
				if (normFac)
					kernel[i][j] /= normFac;
				ker[i][j] = kernel[i][j];
			}
		}
		break;
	}
	}
}




Kernel::~Kernel() {
	for (int i = 0; i < kw; i++)
		delete[] ker[i];
	delete[] ker;
};


double* Kernel::operator[](int i) const {
	cout << endl;
	return ker[i];
}

int Kernel::getKernelWidth() {
	return kw;
}

int Kernel:: getKernelHeight() {
	return kw;
}

const char* Kernel::getKernelName() {
	return kernelName;
}
