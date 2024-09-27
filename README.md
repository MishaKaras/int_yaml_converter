# int_yaml_converter
 
	 Converts int array to string in yaml format or back
## Briefly
This program provides 2 types of functions:
1) Firts type converts integer arrays to their yaml-strings representations.
2) Second type gets string in yaml-format and tries to convert it to an integer array.
## Overloads
Both types of functions have 3 overload, that work with:
1) Null-terminated string (const char \*)
2) Char array with length (const char \* + size_t)
3) std::string instance
## Required packages
1) *gcc* compiler, that supports C++ standart >= 20
2) *cmake* 
3) *doxygen* to make documentation
4) *catch2* v2 to run written tests
5) *gcovr* to check functions coverage by written tests
## Launch
1) Clone repository git clone https://github.com/MishaKaras/intyamlconverter.git
2) Create *build* folder
3) cmake && cd build && make
4) Executable files ***main*** and ***tests*** will be created in *build* folder
5) To see the tests coverage input this command:
	*gcovr -r .. -e CMakeFiles --html-details -o coverage.html .*
	Result can be seen in the **coverage.html** file
6) To make the documentation input:
	*doxygen*
	Result you can see in **html** or **latex** folders
## Contributing
Contributions are welcome! To contribute to the project, please follow these steps:

1. Fork the repository.
2. Create a new branch.
3. Make your changes and commit them (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a Pull Request.
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

MishaKaras - [mickgor@duck.com](mailto:mickgor@duck.com)