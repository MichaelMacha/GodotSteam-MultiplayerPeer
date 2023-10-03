#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "steam_multiplayer_peer/steam_multiplayer_peer.h"
#include "steam_multiplayer_peer/steam_id.h"
#include "steam_multiplayer_peer/steam_connection.h"

#include "godotsteam.h"

using namespace godot;

static Steam *SteamPtr;

void initialize_godotsteam(ModuleInitializationLevel level){
	if(level == MODULE_INITIALIZATION_LEVEL_SCENE){
		ClassDB::register_class<Steam>();
        ClassDB::register_class<SteamMultiplayerPeer>();
        ClassDB::register_class<SteamConnection>();
        ClassDB::register_class<SteamID>();
		SteamPtr = memnew(Steam);
		Engine::get_singleton()->register_singleton("Steam", Steam::get_singleton());
	}
}

void uninitialize_godotsteam(ModuleInitializationLevel level){
	if(level == MODULE_INITIALIZATION_LEVEL_SCENE){
		Engine::get_singleton()->unregister_singleton("Steam");
		memdelete(SteamPtr);
	}
}

extern "C" {
	GDExtensionBool GDE_EXPORT godotsteam_init(GDExtensionInterfaceGetProcAddress p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization){
		godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_initializer(initialize_godotsteam);
		init_obj.register_terminator(uninitialize_godotsteam);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
