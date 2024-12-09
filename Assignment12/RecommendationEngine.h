#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

// Bipartite graph representation
class RecomendationEngine
{
private:
    unordered_map<int, vector<pair<char, int>>> userToMovies; // User -> [(Movie, Rating)]
    unordered_map<char, vector<pair<int, int>>> movieToUsers; // Movie -> [(User, Rating)]

public:
    // Add a rating (edge) to the graph
    // add edge to both userToMovies and movieToUsers
    void addRating(int user, char movie, int rating)
    {
        // Add the movie and rating to the user's list of rated movies
        userToMovies[user].emplace_back(movie, rating);

        // Add the user and rating to the movie's list of users who rated it
        movieToUsers[movie].emplace_back(user, rating);
    }

    // Recommend movies based on a watched movie
    // see assignment for details
    vector<pair<char, double>> recommend(char watchedMovie)
    {
        unordered_map<char, double> movieScores; // Stores aggregated scores for each movie
        unordered_map<char, int> movieCounts;    // Stores the count of contributions for each movie

        for (const auto &[user, watchedRating] : movieToUsers[watchedMovie])
        {
            // Traverse other movies rated by this user
            for (const auto &[otherMovie, otherRating] : userToMovies[user])
            {
                if (otherMovie != watchedMovie)
                { // Avoid recommending the same movie
                    movieScores[otherMovie] += watchedRating * otherRating;
                    movieCounts[otherMovie]++;
                }
            }
        }
        vector<pair<char, double>> recommendations;
        for (const auto &[movie, scoreSum] : movieScores)
        {
            recommendations.emplace_back(movie, scoreSum);
        }

        sort(recommendations.begin(), recommendations.end(),
             [](const auto &a, const auto &b)
             { return a.second > b.second; });

        return recommendations;
    }

    // Print the graph
    void printGraph()
    {
        cout << "User -> Movies:" << endl;
        for (const auto &[user, movies] : userToMovies)
        {
            cout << "User " << user << ": ";
            for (const auto &[movie, rating] : movies)
            {
                cout << "(" << movie << ", " << rating << ") ";
            }
            cout << endl;
        }

        cout << "Movie -> Users:" << endl;
        for (const auto &[movie, users] : movieToUsers)
        {
            cout << "Movie " << movie << ": ";
            for (const auto &[user, rating] : users)
            {
                cout << "(" << user << ", " << rating << ") ";
            }
            cout << endl;
        }
        cout << "\nMovie Recommendations:" << endl;
    }
};
