#pragma once
#include "stdneb.h"
#include "core/types.h"
#include "io/filestream.h"
#include "io/jsonreader.h"
#include "io/jsonwriter.h"

namespace hm
{
	using IO::FileStream;
	using IO::JsonReader;
	using IO::JsonWriter;

	class ISerializable {
		friend class Serializer;
	protected:
		virtual void Serialize(Serializer& writer) = 0;
		virtual void Deserialize(Serializer& reader) = 0;
	};


	class Serializer
	{
		friend class ISerializable;
		FileStream m_File;
		JsonReader m_Reader;
		JsonWriter m_Writer;

		bool m_Reading;
		bool m_Writing;
		int m_Index;
	protected:
		JsonReader& reader;
		JsonWriter& writer;

	public:
		Serializer();
		void BeginRead(const char* file);
		void BeginWrite(const char* file);
		void AddNode(const char* name);
		void AddArrayNode(const char* name);
		template <typename T> void AddData(Util::String& key, T& value);
		void EndNode();
		Util::String GetName();
		bool Next();
		template <typename T> void GetData(const char* key, T& target);
		bool Child();
		bool Parent();
		void Write(ISerializable& item);
		void Read(ISerializable& item);
		void End();

	};

}

template <typename T>
void hm::Serializer::AddData(Util::String& key, T& value) {
	if (m_Writing) {
		m_Writer.Add<T>(&value, key);
	}
}

template <typename T>
void hm::Serializer::GetData(const char* key, T& target) {
	if (m_Reading) {
		m_Reader.Get<T>(target, key);
	}
}