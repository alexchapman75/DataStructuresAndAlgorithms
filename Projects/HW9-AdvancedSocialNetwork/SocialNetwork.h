
#ifndef SOCIAL_NETWORK_H
#define SOCIAL_NETWORK_H

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class SocialNetwork {
public:
    enum class Error {
        SUCCESS,
        USER_ALREADY_EXISTS,
        USER_NOT_FOUND,
        CANNOT_FOLLOW_SELF,
        ALREADY_FOLLOWING,
        NOT_FOLLOWING
      };

private:
    // Represents a single user
    struct User {
        std::string fullname; //Struct instead of a Class because no functions
        std::unordered_set<std::string> following;
        std::list<std::string> posts;
    };

    // Maps username -> User object
    std::unordered_map<std::string, User> users;

public:

    Error addUser(const std::string& username, const std::string& fullname);

    bool isFollowing(const std::string& userA, const std::string& userB);

    Error follow(const std::string& userA, const std::string& userB);

    Error unfollow(const std::string& userA, const std::string& userB);

    std::vector<std::string> mutualFriendSuggestions(const std::string& username);

    Error addPost(const std::string& username, const std::string& postContent);

    Error getPosts(const std::string& username, std::list<std::string>& posts);
};

#endif