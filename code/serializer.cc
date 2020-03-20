#include "serializer.h"
#include "io/uri.h"
#include "io/ioserver.h"


hm::Serializer::Serializer() : m_Index(0), m_Reading(false), m_Writing(false)
{

}

void hm::Serializer::BeginRead(const char* file)
{
	if (m_Reading || m_Writing)
		return;

	Util::String uri("root:");
	uri.Append(file);

	IO::IoServer* io = IO::IoServer::Instance();

	if (!io->FileExists(uri))
		return;

	m_Reading = true;
	m_Reader = IO::JsonReader::Create();

	m_File = IO::FileStream::Create();
	m_File->SetURI(uri);
	m_File->Open();

	m_Reader->SetStream(m_File);
	m_Reader->Open();
}

void hm::Serializer::BeginWrite(const char* file)
{
	if (m_Reading || m_Writing)
		return;

	Util::String uri("root:");
	uri.Append(file);

	IO::IoServer* io = IO::IoServer::Instance();

	if (io->FileExists(uri)) {
		io->DeleteFile(uri);
	}
	m_Writing = true;
	m_Writer = IO::JsonWriter::Create();
	
	m_File = IO::FileStream::Create();
	m_File->SetURI(uri);

	m_Writer->SetStream(m_File);
	m_Writer->Open();

}

void hm::Serializer::AddNode(const char* name)
{
	if (m_Writing) {
		m_Writer->BeginObject(name);
	}
}

void hm::Serializer::AddArrayNode(const char* name)
{
	if (m_Writing) {
		m_Writer->BeginArray(name);
	}
}

void hm::Serializer::EndNode()
{
	if (m_Writing) {
		m_Writer->End();
	}
}

Util::String hm::Serializer::GetName()
{
	if (m_Reading) {
		return m_Reader->GetCurrentNodeName();
	}
	return "";
}

bool hm::Serializer::Next()
{
	if (m_Reading) {
		if (m_Reader->SetToNextChild()) {
			return true;
		}
		else if (m_Reader->SetToNextChild()) {
			return true;
		}
	}
	return false;
}

bool hm::Serializer::Child()
{
	if (m_Reading) {
		return m_Reader->SetToFirstChild();
	}
	return false;
}

bool hm::Serializer::Parent()
{
	if (m_Reading) {
		return m_Reader->SetToParent();
	}
	return false;
}

void hm::Serializer::End()
{
	if (!m_Reading && !m_Writing)
		return;

	if (m_Reading) {
		m_Reading = false;
		m_Reader->Close();
	}
	else if (m_Writing) {
		m_Writing = false;
		m_Writer->Close();
	}

	m_File = nullptr;
	m_Reader = nullptr;
	m_Writer = nullptr;

}
