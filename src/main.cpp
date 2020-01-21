#include <intercept.hpp>

#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>

using namespace intercept;



int intercept::api_version() { //This is required for the plugin to work.
    return INTERCEPT_SDK_API_VERSION;
}

void intercept::register_interfaces() {
    
}

void testThread() {
    client::invoker_lock threadLock;
    sqf::diag_log("After lock");
}

game_value testCmd(game_state& gs) {

    sqf::diag_log("Before Thread");
    std::thread thread(testThread);
    thread.detach();
    sqf::diag_log("After Thread");
    return true;
}

void intercept::pre_start() {
    static auto cmd =
        client::host::register_sqf_command("testCmd", "Test", testCmd, game_data_type::BOOL);
}

void intercept::pre_init() {
    intercept::sqf::system_chat("The Intercept template plugin is running!");
}



// This function is exported and is called by the host at the end of mission initialization.
void intercept::post_init() {

}