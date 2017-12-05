#include <iostream>
#include <string>

#include "addressbook.pb.h"

void test1()
{
	tutorial::AddressBook address_book;

	for (std::size_t i = 0; i < 100; ++i) {
		tutorial::AddressBook next_address_book;

		for (std::size_t j = 0; j < 100; ++j) {
			auto person = next_address_book.add_people();

			person->set_name(std::to_string(j));
			person->set_id(j);

			for (std::size_t k = 0; k < j; ++k)
				person->add_phones()->set_number(std::to_string(k));
		}

		auto address_book_copy = next_address_book;

		if (address_book_copy.people_size() < 1)
			break;

		address_book = address_book_copy;
	}
}

void test2()
{
	auto address_book = std::make_shared<tutorial::AddressBook>();

	for (std::size_t i = 0; i < 100; ++i) {
		auto next_address_book = std::make_shared<tutorial::AddressBook>(*address_book);

		for (std::size_t j = 0; j < 100; ++j) {
			auto person = next_address_book->add_people();

			person->set_name(std::to_string(j));
			person->set_id(j);

			for (std::size_t k = 0; k < j; ++k)
				person->add_phones()->set_number(std::to_string(k));
		}

		auto address_book_copy = next_address_book;

		if (address_book_copy->people_size() < 1)
			break;

		address_book = address_book_copy;
	}
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc != 2) {
		std::cerr << "Usage:  " << argv[0] << " TEST TO RUN { 1, 2 }" << std::endl;

		return -1;
	}

	switch(std::stoul(argv[1])) {
		case 1:
			std::cout << ">>> main running test 1" << std::endl;

			test1();
			break;

		case 2:
			std::cout << ">>> main running test 2" << std::endl;

			test2();
			break;

		default:
			break;
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
