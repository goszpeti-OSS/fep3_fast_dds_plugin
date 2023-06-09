// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file stream_types.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_FEP3_DDSTYPES_STREAM_TYPES_H_
#define _FAST_DDS_GENERATED_FEP3_DDSTYPES_STREAM_TYPES_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(stream_types_SOURCE)
#define stream_types_DllAPI __declspec( dllexport )
#else
#define stream_types_DllAPI __declspec( dllimport )
#endif // stream_types_SOURCE
#else
#define stream_types_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define stream_types_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


namespace fep3 {
    namespace ddstypes {
        /*!
         * @brief This class represents the structure Property defined by the user in the IDL file.
         * @ingroup STREAM_TYPES
         */
        class Property
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport Property();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~Property();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object fep3::ddstypes::Property that will be copied.
             */
            eProsima_user_DllExport Property(
                    const Property& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object fep3::ddstypes::Property that will be copied.
             */
            eProsima_user_DllExport Property(
                    Property&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object fep3::ddstypes::Property that will be copied.
             */
            eProsima_user_DllExport Property& operator =(
                    const Property& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object fep3::ddstypes::Property that will be copied.
             */
            eProsima_user_DllExport Property& operator =(
                    Property&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x fep3::ddstypes::Property object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const Property& x) const;

            /*!
             * @brief Comparison operator.
             * @param x fep3::ddstypes::Property object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const Property& x) const;

            /*!
             * @brief This function copies the value in member name
             * @param _name New value to be copied in member name
             */
            eProsima_user_DllExport void name(
                    const eprosima::fastrtps::fixed_string<256>& _name);

            /*!
             * @brief This function moves the value in member name
             * @param _name New value to be moved in member name
             */
            eProsima_user_DllExport void name(
                    eprosima::fastrtps::fixed_string<256>&& _name);

            /*!
             * @brief This function returns a constant reference to member name
             * @return Constant reference to member name
             */
            eProsima_user_DllExport const eprosima::fastrtps::fixed_string<256>& name() const;

            /*!
             * @brief This function returns a reference to member name
             * @return Reference to member name
             */
            eProsima_user_DllExport eprosima::fastrtps::fixed_string<256>& name();
            /*!
             * @brief This function copies the value in member type
             * @param _type New value to be copied in member type
             */
            eProsima_user_DllExport void type(
                    const eprosima::fastrtps::fixed_string<64>& _type);

            /*!
             * @brief This function moves the value in member type
             * @param _type New value to be moved in member type
             */
            eProsima_user_DllExport void type(
                    eprosima::fastrtps::fixed_string<64>&& _type);

            /*!
             * @brief This function returns a constant reference to member type
             * @return Constant reference to member type
             */
            eProsima_user_DllExport const eprosima::fastrtps::fixed_string<64>& type() const;

            /*!
             * @brief This function returns a reference to member type
             * @return Reference to member type
             */
            eProsima_user_DllExport eprosima::fastrtps::fixed_string<64>& type();
            /*!
             * @brief This function copies the value in member value
             * @param _value New value to be copied in member value
             */
            eProsima_user_DllExport void value(
                    const std::string& _value);

            /*!
             * @brief This function moves the value in member value
             * @param _value New value to be moved in member value
             */
            eProsima_user_DllExport void value(
                    std::string&& _value);

            /*!
             * @brief This function returns a constant reference to member value
             * @return Constant reference to member value
             */
            eProsima_user_DllExport const std::string& value() const;

            /*!
             * @brief This function returns a reference to member value
             * @return Reference to member value
             */
            eProsima_user_DllExport std::string& value();

            /*!
            * @brief This function returns the maximum serialized size of an object
            * depending on the buffer alignment.
            * @param current_alignment Buffer alignment.
            * @return Maximum serialized size.
            */
            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                    const fep3::ddstypes::Property& data,
                    size_t current_alignment = 0);


            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                    eprosima::fastcdr::Cdr& cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                    eprosima::fastcdr::Cdr& cdr);



            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                    eprosima::fastcdr::Cdr& cdr) const;

        private:

            eprosima::fastrtps::fixed_string<256> m_name;
            eprosima::fastrtps::fixed_string<64> m_type;
            std::string m_value;

        };
        /*!
         * @brief This class represents the structure StreamType defined by the user in the IDL file.
         * @ingroup STREAM_TYPES
         */
        class StreamType
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport StreamType();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~StreamType();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object fep3::ddstypes::StreamType that will be copied.
             */
            eProsima_user_DllExport StreamType(
                    const StreamType& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object fep3::ddstypes::StreamType that will be copied.
             */
            eProsima_user_DllExport StreamType(
                    StreamType&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object fep3::ddstypes::StreamType that will be copied.
             */
            eProsima_user_DllExport StreamType& operator =(
                    const StreamType& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object fep3::ddstypes::StreamType that will be copied.
             */
            eProsima_user_DllExport StreamType& operator =(
                    StreamType&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x fep3::ddstypes::StreamType object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const StreamType& x) const;

            /*!
             * @brief Comparison operator.
             * @param x fep3::ddstypes::StreamType object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const StreamType& x) const;

            /*!
             * @brief This function copies the value in member metatype
             * @param _metatype New value to be copied in member metatype
             */
            eProsima_user_DllExport void metatype(
                    const std::string& _metatype);

            /*!
             * @brief This function moves the value in member metatype
             * @param _metatype New value to be moved in member metatype
             */
            eProsima_user_DllExport void metatype(
                    std::string&& _metatype);

            /*!
             * @brief This function returns a constant reference to member metatype
             * @return Constant reference to member metatype
             */
            eProsima_user_DllExport const std::string& metatype() const;

            /*!
             * @brief This function returns a reference to member metatype
             * @return Reference to member metatype
             */
            eProsima_user_DllExport std::string& metatype();
            /*!
             * @brief This function copies the value in member properties
             * @param _properties New value to be copied in member properties
             */
            eProsima_user_DllExport void properties(
                    const std::vector<fep3::ddstypes::Property>& _properties);

            /*!
             * @brief This function moves the value in member properties
             * @param _properties New value to be moved in member properties
             */
            eProsima_user_DllExport void properties(
                    std::vector<fep3::ddstypes::Property>&& _properties);

            /*!
             * @brief This function returns a constant reference to member properties
             * @return Constant reference to member properties
             */
            eProsima_user_DllExport const std::vector<fep3::ddstypes::Property>& properties() const;

            /*!
             * @brief This function returns a reference to member properties
             * @return Reference to member properties
             */
            eProsima_user_DllExport std::vector<fep3::ddstypes::Property>& properties();

            /*!
            * @brief This function returns the maximum serialized size of an object
            * depending on the buffer alignment.
            * @param current_alignment Buffer alignment.
            * @return Maximum serialized size.
            */
            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                    const fep3::ddstypes::StreamType& data,
                    size_t current_alignment = 0);


            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                    eprosima::fastcdr::Cdr& cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                    eprosima::fastcdr::Cdr& cdr);



            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                    eprosima::fastcdr::Cdr& cdr) const;

        private:

            std::string m_metatype;
            std::vector<fep3::ddstypes::Property> m_properties;

        };
        /*!
         * @brief This class represents the structure BusData defined by the user in the IDL file.
         * @ingroup STREAM_TYPES
         */
        class BusData
        {
        public:

            /*!
             * @brief Default constructor.
             */
            eProsima_user_DllExport BusData();

            /*!
             * @brief Default destructor.
             */
            eProsima_user_DllExport ~BusData();

            /*!
             * @brief Copy constructor.
             * @param x Reference to the object fep3::ddstypes::BusData that will be copied.
             */
            eProsima_user_DllExport BusData(
                    const BusData& x);

            /*!
             * @brief Move constructor.
             * @param x Reference to the object fep3::ddstypes::BusData that will be copied.
             */
            eProsima_user_DllExport BusData(
                    BusData&& x) noexcept;

            /*!
             * @brief Copy assignment.
             * @param x Reference to the object fep3::ddstypes::BusData that will be copied.
             */
            eProsima_user_DllExport BusData& operator =(
                    const BusData& x);

            /*!
             * @brief Move assignment.
             * @param x Reference to the object fep3::ddstypes::BusData that will be copied.
             */
            eProsima_user_DllExport BusData& operator =(
                    BusData&& x) noexcept;

            /*!
             * @brief Comparison operator.
             * @param x fep3::ddstypes::BusData object to compare.
             */
            eProsima_user_DllExport bool operator ==(
                    const BusData& x) const;

            /*!
             * @brief Comparison operator.
             * @param x fep3::ddstypes::BusData object to compare.
             */
            eProsima_user_DllExport bool operator !=(
                    const BusData& x) const;

            /*!
             * @brief This function copies the value in member data
             * @param _data New value to be copied in member data
             */
            eProsima_user_DllExport void data(
                    const std::vector<uint8_t>& _data);

            /*!
             * @brief This function moves the value in member data
             * @param _data New value to be moved in member data
             */
            eProsima_user_DllExport void data(
                    std::vector<uint8_t>&& _data);

            /*!
             * @brief This function returns a constant reference to member data
             * @return Constant reference to member data
             */
            eProsima_user_DllExport const std::vector<uint8_t>& data() const;

            /*!
             * @brief This function returns a reference to member data
             * @return Reference to member data
             */
            eProsima_user_DllExport std::vector<uint8_t>& data();

            /*!
            * @brief This function returns the maximum serialized size of an object
            * depending on the buffer alignment.
            * @param current_alignment Buffer alignment.
            * @return Maximum serialized size.
            */
            eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function returns the serialized size of a data depending on the buffer alignment.
             * @param data Data which is calculated its serialized size.
             * @param current_alignment Buffer alignment.
             * @return Serialized size.
             */
            eProsima_user_DllExport static size_t getCdrSerializedSize(
                    const fep3::ddstypes::BusData& data,
                    size_t current_alignment = 0);


            /*!
             * @brief This function serializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serialize(
                    eprosima::fastcdr::Cdr& cdr) const;

            /*!
             * @brief This function deserializes an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void deserialize(
                    eprosima::fastcdr::Cdr& cdr);



            /*!
             * @brief This function returns the maximum serialized size of the Key of an object
             * depending on the buffer alignment.
             * @param current_alignment Buffer alignment.
             * @return Maximum serialized size.
             */
            eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
                    size_t current_alignment = 0);

            /*!
             * @brief This function tells you if the Key has been defined for this type
             */
            eProsima_user_DllExport static bool isKeyDefined();

            /*!
             * @brief This function serializes the key members of an object using CDR serialization.
             * @param cdr CDR serialization object.
             */
            eProsima_user_DllExport void serializeKey(
                    eprosima::fastcdr::Cdr& cdr) const;

        private:

            std::vector<uint8_t> m_data;

        };
    } // namespace ddstypes
} // namespace fep3

#endif // _FAST_DDS_GENERATED_FEP3_DDSTYPES_STREAM_TYPES_H_