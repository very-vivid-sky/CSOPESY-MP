#include <cassert>
#include <cstdlib>
#include <filesystem>
 
int main()
{ 
    // Basic usage
    std::filesystem::create_directories("sandbox/1/2/a");
    std::filesystem::create_directory("sandbox/1/2/b");
 
    // Directory already exists (false returned, no error)
    assert(!std::filesystem::create_directory("sandbox/1/2/b"));
 
    // Permissions copying usage
    std::filesystem::permissions(
        "sandbox/1/2/b",
        std::filesystem::perms::others_all,
        std::filesystem::perm_options::remove
    );
    std::filesystem::create_directory("sandbox/1/2/c", "sandbox/1/2/b");
 
    std::system("dir sandbox\\1\\2");
    std::system("tree sandbox");
    //std::filesystem::remove_all("sandbox");
}