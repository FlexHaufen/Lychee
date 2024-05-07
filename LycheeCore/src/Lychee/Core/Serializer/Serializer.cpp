/**
 * @file Serializer.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Core/Serializer/Serializer.h"

// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {

    Serializer::Serializer(const std::string& filepath, const std::string& filename, bool forceCreation) {
        if (std::filesystem::exists(filepath)) {
            m_FilePath = filepath;
            m_FileName = filename;
            return;
        }
        else if (forceCreation) {
            LY_CORE_INFO("Serializer: Creating new savefilepath [{0}]", filepath);
            std::filesystem::create_directories(filepath);
            return;
        }
        LY_CORE_ERROR("Serializer: Could not find / create savefilepath [{0}]", filepath);
    };

    template<typename T>
    void Serializer::SerializeValue(const std::string& key, const T& value) const {
        
        YAML::Node config;
        std::string yamlFile = m_FilePath + m_FileName;

        // Load existing YAML file if it exists
        std::ifstream fin(yamlFile);
        if (fin.good()) {
            fin.close();
            config = YAML::LoadFile(yamlFile);
        } else {
            LY_CORE_INFO("Serializer: File [{0}] does not exist, creating new one", m_FileName);
        }
        
        config[key] = value;

        std::ofstream fout(yamlFile);
        fout << config;
        fout.close();
    }

    template<typename T>
    bool Serializer::DeserializeValue(const std::string& key, T& value) const {
        std::string yamlFile = m_FilePath + m_FileName;
        try {
            YAML::Node config = YAML::LoadFile(yamlFile);
            if (!config[key]) {
                LY_CORE_ERROR("Serializer: Could not find key [{0}] in file [{1}]", key, m_FileName);
                return false;
            }

            try {
                value = config[key].as<T>();
                return true;
            } 
            catch (const YAML::Exception& e) {
                LY_CORE_ERROR("Serializer: Error converting YAML value to the specified type: [{0}]", e.what());
                return false;
            }
        }
        catch (const YAML::Exception& e) {
            LY_CORE_ERROR("Serializer: Error loading YAML file [{0}]", e.what());
            return false;
        }
        return false;
    }
}