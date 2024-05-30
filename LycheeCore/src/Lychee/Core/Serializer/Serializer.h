/**
 * @file Serializer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include <string>

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {


    // TODO (flex): ErrorHandling with serialization
    class Serializer {
    public:

        /**
         * @brief Construct a new Serializer object
         * 
         * @param filepath      filepath to save file to (has to end with "/")
         * @param filename      filename
         * @param forceCreation true: filepath will be created if it does not exist
         */
        Serializer(const std::string& filepath, const std::string& filename, bool forceCreation = true);

        /**
         * @brief Serialize a value to YAML-File
         * 
         * @tparam T    Value type
         * @param key
         * @param value   
         */
        template<typename T>
        void SerializeValue(const std::string& key, const T& value) const;

        /**
         * @brief Deserialize a value from YAML-File
         * 
         * @tparam T    Value type
         * @param key   
         * @param value 
         * @return b8   true: successful, false: error
         */
        template<typename T>
        bool DeserializeValue(const std::string& key, T& value) const;

    private:

        // ** Members **
        std::string m_FilePath;     // SavePath of YAML file
        std::string m_FileName;     // Filename of YAML file

    };
}