class Matrix {
 public:
   Matrix(unsigned rows, unsigned cols);
   double& operator() (unsigned row, unsigned col);       
   double  operator() (unsigned row, unsigned col) const;

  ~Matrix();                              // Destructor
   Matrix(const Matrix& m);               // Copy constructor
   Matrix& operator= (const Matrix& m);   // Assignment operator
 
 private:
   unsigned rows_, cols_;
   double* data_;
 };
 
 inline
 Matrix::Matrix(unsigned rows, unsigned cols)
   : rows_ (rows)
   , cols_ (cols)
   //data_ <--initialized below (after the 'if/throw' statement)
 {
	 try
	 {
			if (rows == 0 || cols == 0)
				throw 19;
	 }
   catch(int e)
	 {
		 cout << "Matrix constructor has 0 size, error nr:" << e;
	 }
   data_ = new double[rows * cols];
 }
 
 inline
 Matrix::~Matrix()
 {
   delete[] data_;
 }
 
 inline
 double& Matrix::operator() (unsigned row, unsigned col)
 {
	 try
	 {
			if (row >= rows_ || col >= cols_)
				throw 20;
	 }
   catch(int e)
	 {
		 cout << "Matrix subscript out of bounds, error nr:" << e;
	 }
   return data_[cols_*row + col];
 }
 
 inline
 double Matrix::operator() (unsigned row, unsigned col) const
 {
	 try
	 {
			if (row >= rows_ || col >= cols_)
				throw 21;
	 }
   catch(int e)
	 {
		 cout << "const Matrix subscript out of bounds, error nr:" << e;
	 }
     //throw BadIndex("const Matrix subscript out of bounds");
   return data_[cols_*row + col];
 } 