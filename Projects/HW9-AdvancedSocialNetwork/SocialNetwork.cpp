#include "SocialNetwork.h"

// addUser: Adds a new user
SocialNetwork::Error SocialNetwork::addUser(const std::string& username, const std::string& fullname) {
    // Check if user already exists
    if (users.find(username) != users.end()) {
        return Error::USER_ALREADY_EXISTS;
    }

    // Create new user
    users[username] = {fullname, {}, {}};
    return Error::SUCCESS;
}

// isFollowing: Checks if userA follows userB
bool SocialNetwork::isFollowing(const std::string& userA, const std::string& userB) {
    // If either user does not exist, return false
    if (users.find(userA) == users.end() || users.find(userB) == users.end()) {
        return false;
    }

    // Check if userB is in userA's following set
    return users[userA].following.count(userB);
}

// follow: userA follows userB
SocialNetwork::Error SocialNetwork::follow(const std::string& userA, const std::string& userB) {
    // Check both users exist
    if (users.find(userA) == users.end() || users.find(userB) == users.end()) {
        return Error::USER_NOT_FOUND;
    }

    // Prevent self-follow
    if (userA == userB) {
        return Error::CANNOT_FOLLOW_SELF;
    }

    // Prevent duplicate follow
    if (users[userA].following.count(userB)) {
        return Error::ALREADY_FOLLOWING;
    }

    // Add follow relationship
    users[userA].following.insert(userB);
    return Error::SUCCESS;
}

// unfollow: userA unfollows userB
SocialNetwork::Error SocialNetwork::unfollow(const std::string& userA, const std::string& userB) {
    // Check both users exist
    if (users.find(userA) == users.end() || users.find(userB) == users.end()) {
        return Error::USER_NOT_FOUND;
    }

    // Check if userA is actually following userB
    if (!users[userA].following.count(userB)) {
        return Error::NOT_FOLLOWING;
    }

    // Remove follow relationship
    users[userA].following.erase(userB);
    return Error::SUCCESS;
}

// mutualFriendSuggestions
std::vector<std::string> SocialNetwork::mutualFriendSuggestions(const std::string& username) {
    std::vector<std::string> result;

    // Check if user exists
    if (users.find(username) == users.end()) {
        return result;
    }

    const auto& followingSet = users[username].following;

    // If user follows nobody → no suggestions
    if (followingSet.empty()) {
        return result;
    }

    // Initialize intersection with first followed user's following list
    auto it = followingSet.begin();
    std::unordered_set<std::string> intersection = users[*it].following;
    ++it;

    // Intersect with remaining users
    for (; it != followingSet.end(); ++it) {
        std::unordered_set<std::string> temp;

        for (const auto& user : intersection) {
            if (users[*it].following.count(user)) {
                temp.insert(user);
            }
        }

        intersection = temp;
    }

    // Filter out:
    // - original user
    // - users already followed
    for (const auto& user : intersection) {
        if (user != username && !followingSet.count(user)) {
            result.push_back(user);
        }
    }

    return result;
}

// addPost: Adds a post for a user
SocialNetwork::Error SocialNetwork::addPost(const std::string& username, const std::string& postContent) {
    // Check if user exists
    if (users.find(username) == users.end()) {
        return Error::USER_NOT_FOUND;
    }

    // Add post to end (preserves order)
    users[username].posts.push_back(postContent);
    return Error::SUCCESS;
}

// getPosts: Retrieves posts for a user
SocialNetwork::Error SocialNetwork::getPosts(const std::string& username, std::list<std::string>& posts) {
    // Check if user exists
    if (users.find(username) == users.end()) {
        return Error::USER_NOT_FOUND;
    }

    // Copy posts into provided list
    posts = users[username].posts;
    return Error::SUCCESS;
}