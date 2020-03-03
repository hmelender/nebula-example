#include "serializer.h"
#include "io/uri.h"
#include "io/ioserver.h"


hm::Serializer::Serializer() : m_Reading(false), m_Writing(false), reader(m_Reader), writer(m_Writer)
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

	m_File.SetURI(uri);
	m_File.Open();

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

	m_File.SetURI(uri);
	m_File.Open();

}

void hm::Serializer::AddNode(const char* name)
{
	if (m_Writing) {
		m_Writer.BeginObject(name);
	}
}

void hm::Serializer::AddArrayNode(const char* name)
{
	if (m_Writing) {
		m_Writer.BeginArray(name);
	}
}

void hm::Serializer::EndNode()
{
	if (m_Writing) {
		m_Writer.End();
	}
}

Util::String hm::Serializer::GetName()
{
	if (m_Reading) {
		return m_Reader.GetCurrentNodeName();
	}
	return "";
}

bool hm::Serializer::Next()
{
	if (m_Reading) {
		return m_Reader.SetToNextChild();
	}
	return false;
}

bool hm::Serializer::Child()
{
	if (m_Reading) {
		return m_Reader.SetToFirstChild();
	}
	return false;
}

bool hm::Serializer::Parent()
{
	if (m_Reading) {
		return m_Reader.SetToParent();
	}
	return false;
}

void hm::Serializer::Write(ISerializable& item)
{
	item.Serialize(*this);
}

void hm::Serializer::Read(ISerializable& item)
{
	item.Deserialize(*this);
}

void hm::Serializer::End()
{
	if (!m_Reading && !m_Writing)
		return;

	m_File.Close();
}
