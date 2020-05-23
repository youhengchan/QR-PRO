#pragma once
#include <string>

class QRFactory
{
private:
	std::string QRRaw;
public:
	
	QRFactory();
	~QRFactory();
	void SetQRInfo(const std::string & str);
	void GetQRInfo() const;
	void GeneratePNG() const;
	void GenerateBMP() const;
	void GenerateJPG() const;
	void GenerateJIF() const;
};

