#pragma once
#include "stdneb.h"
#include "core/types.h"
#include "util/variant.h"

namespace hm
{
	using Core::RefCounted;

	class Variant : public Util::Variant
	{
	public:
		using Util::Variant::Variant;

		operator byte() { return this->GetByte(); };
		operator short() { return this->GetShort(); };
		operator ushort() { return this->GetUShort(); };
		operator int() { return this->GetInt(); };
		operator uint() { return this->GetUInt(); };
		operator int64_t() { return this->GetInt64(); };
		operator uint64_t() { return this->GetUInt64(); };
		operator float() { return this->GetFloat(); };
		operator double() { return this->GetDouble(); };
		operator bool() { return this->GetBool(); };
		operator Math::float2() { return this->GetFloat2(); };
		operator Math::float4() { return this->GetFloat4(); };
		operator Math::quaternion& () { return this->GetQuaternion(); };
		operator const Math::matrix44& () { return this->GetMatrix44(); };
		operator const Math::transform44& () { return this->GetTransform44(); };
		operator const Util::String& () { return this->GetString(); };
		operator Core::RefCounted* () { return this->GetObject(); };
	
	};

}