CXX = clang++
CXXFLAGS = -std=c++17 -stdlib=libc++ -Wall -Wextra

# Ścieżki do nagłówków i bibliotek MySQL Connector/C++
INCLUDES = -I/usr/local/mysql-connector-c++-8.4.0/include
LIBS = -L/usr/local/mysql-connector-c++-8.4.0/lib64 -lmysqlcppconn8 -lmysqlcppconn


SRC = main.cpp Database.cpp User.cpp UserRepository.cpp BaseRepository.cpp Book.cpp BookRepository.cpp Validation.cpp Loan.cpp LoanRepository.cpp
OUT = app

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(OUT)

run: $(OUT)
	DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++-8.4.0/lib64 ./$(OUT)

clean:
	rm -f $(OUT)