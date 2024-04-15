#pragma once

// Program assumes its working directory is the project
#define path_config                              "./Source/Config/"
#define path_module_gasa                         "./Source/Gasa/"
#define path_gasa_ability_system path_module_gasa "AbilitySystem/"

#pragma region Globals
// These Code objects are created before anything else after gencpp does its initializatioon
global Code umeta_uclass;
global Code umeta_generated_body;
global Code gasa_api;
#pragma endregion Globals
