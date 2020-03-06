#pragma once
#include "stdneb.h"
#include "core/types.h"
#include "io/filestream.h"
#include "io/jsonreader.h"
#include "io/jsonwriter.h"
#include "util/stringatom.h"
#include "util/string.h"
#include "math/float4.h"
#include "math/quaternion.h"
#include "math/point.h"

namespace hm
{
	using IO::FileStream;
	using IO::JsonReader;
	using IO::JsonWriter;

	class ISerializable {
		friend class Serializer;
	public:
		virtual ~ISerializable() {};
		virtual void Serialize(Serializer& writer) = 0;
		virtual void Deserialize(Serializer& reader) = 0;
	};


	class Serializer
	{
		friend class ISerializable;
		FileStream* m_File;
		JsonReader* m_Reader;
		JsonWriter* m_Writer;

		bool m_Reading;
		bool m_Writing;
		int m_Index;

	public:
		Serializer();
		void BeginRead(const char* file);
		void BeginWrite(const char* file);
		void AddNode(const char* name);
		void AddArrayNode(const char* name);
		void EndNode();
		Util::String GetName();
		bool Next();
		bool Child();
		bool Parent();
		void End();


		template <typename T>
		void AddData(Util::String key, const T& value) {
			if (m_Writing) {
				m_Writer->Add<T>(value, key);
			}
		};

		template <>
		void AddData(Util::String key, const Util::StringAtom& value) {
			Util::String s(value.AsString());
			if (m_Writing) {
				m_Writer->Add(s, key);
			}
		};

		template <>
		void AddData(Util::String key, const Math::point& value) {
			Math::float4 f(value);
			if (m_Writing) {
				m_Writer->Add(f, key);
			}
		};

		template <>
		void AddData(Util::String key, const Math::quaternion& value) {
			Math::float4 f(value.x(), value.y(), value.z(), value.w());
			if (m_Writing) {
				m_Writer->Add(f, key);
			}
		};

		template <typename T>
		void GetData(const char* key, T& target) {
			if (m_Reading) {
				m_Reader->Get<T>(target, key);
			}
		};

		template <>
		void GetData(const char* key, Util::StringAtom& target) {
			if (m_Reading) {
				target = m_Reader->GetString(key);
			}
		};

		template <>
		void GetData(const char* key, Math::float4& target) {
			if (m_Reading) {
				target = m_Reader->GetFloat4(key);
			}
		};

		template <>
		void GetData(const char* key, Math::point& target) {
			if (m_Reading) {
				target = m_Reader->GetFloat4(key);
			}
		};

		template <>
		void GetData(const char* key, Math::quaternion& target) {
			if (m_Reading) {
				target.set(m_Reader->GetFloat4(key));
			}
		};

	};

}
