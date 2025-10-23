#include <iostream>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>
#include <thread>

std::string sBerechneMD5(const std::string &sEingabe) {
	boost::uuids::detail::md5 md5;
	md5.process_bytes(sEingabe.data(), sEingabe.size());
	unsigned int iBerechne[4];
	md5.get_digest(iBerechne);
	std::string sErgebnis;
	boost::algorithm::hex(iBerechne, iBerechne + 4,
			std::back_inserter(sErgebnis));
	return sErgebnis;
}

void worker(int id) {

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

int main() {
	//thread test

	std::vector<std::thread> workers;
	for (int i = 0; i < 5; ++i) {
		workers.push_back(std::thread(worker, i));
	}
	for (auto &t : workers) {
		t.join();
	}
	std::cout << "Thread test abgeschlossen.\n";

	std::string sMd5 = "07811dc6c422334ce36a09ff5cd6fe71";
	int a = 0, b = 0;
	std::cout << "Geben Sie den MD5 ein: " << std::endl;
	std::cin >> sMd5;
	std::cout << std::endl << "Geben Sie den ersten Wert ein: " << std::endl;
	std::cin >> a;
	std::cout << std::endl << "Geben Sie den zweiten Wert ein: " << std::endl;
	std::cin >> b;
	std::cout << std::endl;

	// Brute-Force-Ansatz: Testen von Zahlen von 0 bis 9999
	for (int i = 0; i <= 9999; ++i) {
		std::string sEingabe = std::to_string(i);
		std::string sMD5Hash = sBerechneMD5(sEingabe);
		if (boost::iequals(sMD5Hash, sMd5)) {
			std::cout << "MD5-Wert gefunden:" << i << std::endl;
			std::cout << "Das Ergebnis von a (" << a << ") + b (" << b
					<< ") * MD5 (" << i << ") ist: "
					<< std::to_string(a + b * i) << std::endl;
			return 0;
		}
	}
	std::cout << "Fehler bei der Eingabe";
	return 1;
}
