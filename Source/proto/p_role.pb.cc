// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: p_role.proto

#include "p_role.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr P_RoleData::P_RoleData(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : role_name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , role_id_(0u){}
struct P_RoleDataDefaultTypeInternal {
  constexpr P_RoleDataDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~P_RoleDataDefaultTypeInternal() {}
  union {
    P_RoleData _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT P_RoleDataDefaultTypeInternal _P_RoleData_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_p_5frole_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_p_5frole_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_p_5frole_2eproto = nullptr;

const uint32_t TableStruct_p_5frole_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::P_RoleData, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::P_RoleData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::P_RoleData, role_id_),
  PROTOBUF_FIELD_OFFSET(::P_RoleData, role_name_),
  1,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, -1, sizeof(::P_RoleData)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_P_RoleData_default_instance_),
};

const char descriptor_table_protodef_p_5frole_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014p_role.proto\"0\n\nP_RoleData\022\017\n\007role_id\030"
  "\001 \001(\r\022\021\n\trole_name\030\002 \001(\t"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_p_5frole_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_p_5frole_2eproto = {
  false, false, 64, descriptor_table_protodef_p_5frole_2eproto, "p_role.proto", 
  &descriptor_table_p_5frole_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_p_5frole_2eproto::offsets,
  file_level_metadata_p_5frole_2eproto, file_level_enum_descriptors_p_5frole_2eproto, file_level_service_descriptors_p_5frole_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_p_5frole_2eproto_getter() {
  return &descriptor_table_p_5frole_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_p_5frole_2eproto(&descriptor_table_p_5frole_2eproto);

// ===================================================================

class P_RoleData::_Internal {
 public:
  using HasBits = decltype(std::declval<P_RoleData>()._has_bits_);
  static void set_has_role_id(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_role_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

P_RoleData::P_RoleData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:P_RoleData)
}
P_RoleData::P_RoleData(const P_RoleData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  role_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    role_name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_role_name()) {
    role_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_role_name(), 
      GetArenaForAllocation());
  }
  role_id_ = from.role_id_;
  // @@protoc_insertion_point(copy_constructor:P_RoleData)
}

inline void P_RoleData::SharedCtor() {
role_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  role_name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
role_id_ = 0u;
}

P_RoleData::~P_RoleData() {
  // @@protoc_insertion_point(destructor:P_RoleData)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void P_RoleData::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  role_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void P_RoleData::ArenaDtor(void* object) {
  P_RoleData* _this = reinterpret_cast< P_RoleData* >(object);
  (void)_this;
}
void P_RoleData::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void P_RoleData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void P_RoleData::Clear() {
// @@protoc_insertion_point(message_clear_start:P_RoleData)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    role_name_.ClearNonDefaultToEmpty();
  }
  role_id_ = 0u;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* P_RoleData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional uint32 role_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_role_id(&has_bits);
          role_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional string role_name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_role_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "P_RoleData.role_name");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* P_RoleData::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:P_RoleData)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 role_id = 1;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_role_id(), target);
  }

  // optional string role_name = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_role_name().data(), static_cast<int>(this->_internal_role_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "P_RoleData.role_name");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_role_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:P_RoleData)
  return target;
}

size_t P_RoleData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:P_RoleData)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional string role_name = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_role_name());
    }

    // optional uint32 role_id = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_role_id());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData P_RoleData::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    P_RoleData::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*P_RoleData::GetClassData() const { return &_class_data_; }

void P_RoleData::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<P_RoleData *>(to)->MergeFrom(
      static_cast<const P_RoleData &>(from));
}


void P_RoleData::MergeFrom(const P_RoleData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:P_RoleData)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_role_name(from._internal_role_name());
    }
    if (cached_has_bits & 0x00000002u) {
      role_id_ = from.role_id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void P_RoleData::CopyFrom(const P_RoleData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:P_RoleData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool P_RoleData::IsInitialized() const {
  return true;
}

void P_RoleData::InternalSwap(P_RoleData* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &role_name_, lhs_arena,
      &other->role_name_, rhs_arena
  );
  swap(role_id_, other->role_id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata P_RoleData::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_p_5frole_2eproto_getter, &descriptor_table_p_5frole_2eproto_once,
      file_level_metadata_p_5frole_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::P_RoleData* Arena::CreateMaybeMessage< ::P_RoleData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::P_RoleData >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
