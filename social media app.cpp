#include<iostream>
using namespace std;
class Post;  // Forward declaration 
class date {
    int day, month, year;
public:
    date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }
    void printdate() const {
        cout << day << "/" << month << "/" << year << endl;
    }
    ~date() {
        day = 0;
        month = 0;
        year = 0;
    }
};
class Comment {
    string commenterName;
    string content;
public:
    Comment(string name, string c) {
        commenterName = name;
        content = c;
    }
    void showComment() {
        cout << commenterName << " commented: " << content << endl;
    }
};
class PageManage {
    string IDp;
    string namep;
    PageManage** pages;
    int pageCount;
public:
    PageManage(string i, string n) {
        IDp = i;
        namep = n;
        pageCount = 0;
        pages = new PageManage * [10];
    }
    string getID() const { return IDp; }
    string getName() const { return namep; }

    void likePage(PageManage* p) {
        if (pageCount < 10)
            pages[pageCount++] = p;
    }

    void dislikePage(PageManage* p) {
        for (int i = 0; i < pageCount; i++) {
            if (pages[i] == p) {
                for (int j = i; j < pageCount - 1; j++) {
                    pages[j] = pages[j + 1];
                }
                pageCount--;
                break;
            }
        }
    }
    void viewLikedPages(string userName) {
        cout << "Liked pages of " << userName << ":" << endl;
        for (int i = 0; i < pageCount; i++) {
            cout << pages[i]->getID() << " - " << pages[i]->getName() << endl;
        }
    }
    ~PageManage() { delete[] pages; }
};
class User {
    string ID;
    string name;
    User** friends;
    int friendCount;
    Post** posts;
    int postCount;
public:
    User(string i, string n) {
        ID = i;
        name = n;
        friends = new User * [10];
        friendCount = 0;
        posts = new Post * [10];
        postCount = 0;
    }
    string getName() const { return name; }
    string getID() const { return ID; }
    void setUser() {
        cout << "Set current user " << ID << endl;
        cout << name << " successfully set as Current User" << endl;
    }
    void addFriend(User* f) {
        if (friendCount < 10)
            friends[friendCount++] = f;
    }
    void viewFriendList() {
        cout << "Friends list of " << name << ": " << endl;
        for (int i = 0; i < friendCount; i++) {
            cout << friends[i]->ID << " " << friends[i]->name << endl;
        }
    }
    void createPost(Post* p);
    void viewpage(PageManage* p, User* username);
    void viewTimeline();
    void memories(Post* oldpost1, Post* oldpost2);
    Post** getPosts() { return posts; }
    int getPostCount() { return postCount; }
    User** getFriends() { return friends; }
    int getFriendCount() { return friendCount; }
    ~User() {
        for (int i = 0; i < postCount; i++)
            delete posts[i];
        delete[] posts;
        delete[] friends;  
    }

};
class Post {
    string content;
    User* author;
    int likeCount;
    User** likedBy;
    Comment** comments;
    int commentCount;
    int shareCount;
    date Date;
    PageManage* page;
public:
    Post(int d, int m, int y, User* u, string c) : Date(d, m, y) {
        content = c;
        author = u;
        likeCount = 0;
        likedBy = new User * [10];
        comments = new Comment * [10];
        commentCount = 0;
        shareCount = 0;
        page = nullptr;
    }
    Post(int d, int m, int y, PageManage* p, string c) : Date(d, m, y) {
        content = c;
        page = p;
        likeCount = 0;
        likedBy = new User * [10];
        comments = new Comment * [10];
        commentCount = 0;
        shareCount = 0;
        author = nullptr;
    }
    void likePost(User* u) {
        for (int i = 0; i < likeCount; i++) {
            if (likedBy[i] == u) {
                cout << u->getName() << " already liked this post." << endl;
                return;
            }
        }
        likedBy[likeCount++] = u;
        cout << u->getName() << " liked the post." << endl;
    }
    void viewlikedlist() {
        cout << "post liked by: " << endl;
        for (int i = 0; i < likeCount; i++) {
            cout << likedBy[i]->getID() << " " << likedBy[i]->getName() << endl;
        }
    }
    void addComment(Comment* c) {
        if (commentCount < 10)
            comments[commentCount++] = c;
    }
    void sharePost() {
        shareCount++;
        cout << "Post shared. Total shares: " << shareCount << endl;
    }
    void display() const {
        if (author) {
            cout << author->getName() << " posted on ";
        }
        else if (page) {
            cout << page->getName() << " posted on ";
        }
        Date.printdate();
        cout << content << endl;
        cout << "Likes: " << likeCount << ", Shares: " << shareCount << endl;
        for (int i = 0; i < commentCount; i++)
            comments[i]->showComment();
    }
    ~Post() {
        delete[] likedBy;
        for (int i = 0; i < commentCount; i++) delete comments[i];
        delete[] comments;
    }
};
void User::createPost(Post* p) {
    if (postCount < 10)
        posts[postCount++] = p;
}
void User::viewpage(PageManage* p, User* username) {
    cout << p->getName() << endl;
    string id = p->getID(); 
    if (username->getID() == "u1") {
        if (id == "p1") {
            Post foodPost1(14, 3, 2025, p, "Food Fusion is making Kashmiri Chai (Pink Tea). Try this at home...");
            foodPost1.display();
            Comment* fc1 = new Comment("Food Fusion", "Followers please try this recipe and give your feedback");
            Comment* fc2 = new Comment("Amna Akram", "yummy");
            fc1->showComment();
            fc2->showComment();
            Post foodPost2(13, 3, 2025, p, "Food Fusion is making Halwa Puri. Sunday Special Breakfast for our followers...");
            foodPost2.display();
            Comment* fc3 = new Comment("Fatima", "it looks tasty");
            Comment* fc4 = new Comment("Mariyam Akram", "Will try it soon");
            fc3->showComment();
            fc4->showComment();
        }
        else if (id == "p2") {
            Post alJazeeraPost(10, 3, 2025, p, "Breaking news: World leaders meet to discuss climate change.");
            alJazeeraPost.display();
        }
        else if (id == "p3") {
            Post bbcPost(12, 3, 2025, p, "New technology advances in space exploration announced today.");
            bbcPost.display();
        }
        else {
            cout << "No posts available for this page." << endl;
        }
    }
    if (username->getID() == "u2") {
        if (id == "p1") {
            Post HK(14, 3, 2025, p, "OUR NEW DIAMOND RING IS OUT!!");
            HK.display();
            Comment* fc1 = new Comment("HK", "buy it at our store and online");
            Comment* fc2 = new Comment("Amna", "pretty");
            fc1->showComment();
            fc2->showComment();
            Post HK2(13, 3, 2025, p, "NEW JEWELLERY SET LAUNCHING SOON!");
            HK2.display();
            Comment* fc3 = new Comment("Fatima", "waiting...");
            Comment* fc4 = new Comment("Mariyam Akram", "please share the price too");
            fc3->showComment();
            fc4->showComment();
        }
        else if (id == "p3") {
            Post CNN1(10, 3, 2025, p, "Breaking news: World leaders meet to discuss climate change.");
            CNN1.display();
        }
        else if (id == "p4") {
            Post amazon(12, 3, 2025, p, "New technology advances in space exploration announced today.");
            amazon.display();
        }
        else {
            cout << "No posts available for this page." << endl;
        }
    }
    if (username->getID() == "u3") {
        if (id == "p1") {
            Post nike1(14, 3, 2025, p, "New launch!! coming soon");
            nike1.display();
            Comment* fc1 = new Comment("Mariyam", "can't wait");
            Comment* fc2 = new Comment("Amna", "omg");
            fc1->showComment();
            fc2->showComment();
            Post nike2(13, 3, 2025, p, "check out our new sneakers collection for this month");
            nike2.display();
            Comment* fc3 = new Comment("Fatima", "Amazing");
            Comment* fc4 = new Comment("Mariyam Akram", "please share the price too");
            fc3->showComment();
            fc4->showComment();
        }
        else if (id == "p3") {
            Post google(10, 3, 2025, p, "GET READY TO MEET GOOGLEIO");
            google.display();
        }
        else if (id == "p4") {
            Post christiano(12, 3, 2025, p, "family time");
            christiano.display();
        }
        else {
            cout << "No posts available for this page." << endl;
        }
    }
}
void User::viewTimeline() {
    cout << "--- Timeline of " << name << " ---" << endl;
    for (int i = 0; i < postCount; i++) posts[i]->display();
    for (int i = 0; i < friendCount; i++) {
        User* f = friends[i];
        for (int j = 0; j < f->getPostCount(); j++) f->getPosts()[j]->display();
    }
}
void User:: memories(Post* oldpost1, Post* oldpost2) {
    cout << "------memories------" << endl;
    oldpost1->display();
    oldpost2->display();

}
class homepage{
    string caption;
    string type;
    string value;
    string name;
public:
    homepage(User* f, string c, int t, string v) {
        name = f->getName();
        caption = c;
        if (t == 0) {
            type = " ";
        }
        else if (t == 1) {
            type = "feeling";
        }
        else if (t == 2) {
            type = "thinking about";
        }
        else if (t == 3) {
            type = "Making";
        }
        else if (t == 4) {
            type = "celebrating";
        }
        value = v;
    }
    homepage(PageManage* p, string c, int t, string v) {
        name = p->getName();
        caption = c;
        if (t == 0) {
            type = " ";
        }
        else if (t == 1) {
            type = "feeling";
        }
        else if (t == 2) {
            type = "thinking about";
        }
        else if (t == 3) {
            type = "Making";
        }
        else if (t == 4) {
            type = "celebrating";
        }
        value = v;
    }
    homepage(User* f, string c, string v) {
        name = f->getName();
        caption = c;
        value = v;
    }
    void showhomepage() {
        if (type == " ") {
            cout << name << " " << value << " " << caption << endl;
        }
        else {
            cout << name << " is " << type << " " << value << endl;
            cout << caption << endl;
        }
    }
};
class socialmediarun {
    User* username;
public:
    socialmediarun(User* name) {
        username = name;
    }
    void run() {
        if (username->getID() == "u1") {
            date d(15, 3, 2025);
            d.printdate();
            User u1("u1", "Fatima");
            u1.setUser();
            User u2("u2", "Abeeha ");
            User u3("u3", "Ahsan Ali");
            User u4("u4", "Ali Ahmed");
            u1.addFriend(&u2);
            u1.addFriend(&u3);
            u1.addFriend(&u4);
            u1.viewFriendList();
            PageManage p1("p1", "Food Fusion");
            PageManage p2("p2", "Al Jazeera");
            PageManage p3("p3", "BBC News");
            PageManage manager("", "");
            manager.likePage(&p1);
            manager.likePage(&p2);
            manager.likePage(&p3);
            manager.viewLikedPages(u1.getName());
            manager.dislikePage(&p2);
            cout << "After disliking a page:" << endl;
            manager.viewLikedPages(u1.getName());
            cout << "-------homepage-------" << endl;
            homepage f1(&u2, "OOP Project Started Yayy...", 1, "excited");
            f1.showhomepage();
            Comment* c3 = new Comment("Amna Akram", "Best of Luck");
            Comment* c4 = new Comment("Fatima", "Interesting");
            c3->showComment();
            c4->showComment();
            homepage f2(&u3, "Waiting for Weekend", 0, "shared");
            f2.showhomepage();
            Comment* c5 = new Comment("Saad Ali", "Any plans for Get Together?");
            Comment* c6 = new Comment("Abdullah Nadeem", "Yes BBQ");
            c5->showComment();
            c6->showComment();
            homepage f3(&u4, "Waiting for Result", 0, "shared");
            f3.showhomepage();
            homepage f4(&p1, "Try this at home...", 3, "Kashmiri Chai (Pink Tea)");
            f4.showhomepage();
            Comment* c7 = new Comment("Food Fusion", "Followers please try this recipe and give your feedback");
            Comment* c8 = new Comment("Amna Akram", "yummy");
            c7->showComment();
            c8->showComment();
            homepage f5(&p3, "Oil drilling in Alaska & #39; s indigenous communities is on the table again", 0, "shared");
            f5.showhomepage();
            // Posts
            Post* post1 = new Post(14, 3, 2025, &u1, "Just joined this awesome platform!");
            u1.createPost(post1);
            Post* post2 = new Post(15, 3, 2025, &u1, "enjoying the weather");
            u1.createPost(post2);
            // Likes
            post1->likePost(&u3);
            post1->likePost(&u4);
            post1->likePost(&u3); // duplicate like test
            post2->likePost(&u3);
            post2->likePost(&u4);
            post2->likePost(&u2);
            // Comments
            Comment* c1 = new Comment("Ahsan Ali", "Congrats!");
            Comment* c2 = new Comment("Ali Ahmed", "Welcome!");
            post1->addComment(c1);
            post1->addComment(c2);
            Comment* c9 = new Comment("Ahsan Ali", "yeah it's good");
            post2->addComment(c9);
            // Share
            post1->sharePost();
            post2->sharePost();
            post2->sharePost();
            Post* oldPost1 = new Post(14, 3, 2024, &u1, "This is a post from last year!");
            u1.createPost(oldPost1);
            Post* oldPost2 = new Post(15, 2, 2024, &u1, "Another memory from last year");
            u1.createPost(oldPost2);
            u1.memories(oldPost1, oldPost2);
            // View timeline
            u1.viewTimeline();
            post1->viewlikedlist();
            post2->viewlikedlist();
            u1.viewpage(&p1,&u1);
            u1.viewpage(&p3,&u1);
        }
        else if (username->getID() == "u2") {
            date d(15, 3, 2025);
            d.printdate();
            User u2("u2", "Abeeha");
            u2.setUser();
            User u1("u1", "Fatima");
            User u3("u3", "Ahsan Ali");
            User u4("u4", "Ali Ahmed");
            User u5("u5", "Mariyam");
            u2.addFriend(&u1);
            u2.addFriend(&u3);
            u2.addFriend(&u4);
            u2.addFriend(&u5);
            u2.viewFriendList();
            PageManage p1("p1", "HK jewellery");
            PageManage p2("p2", "Al Jazeera");
            PageManage p3("p3", "CNN News");
            PageManage p4("p4", "Amazon");
            PageManage manager("", "");
            manager.likePage(&p1);
            manager.likePage(&p2);
            manager.likePage(&p3);
            manager.likePage(&p4);
            manager.viewLikedPages(u2.getName());
            manager.dislikePage(&p2);
            cout << "After disliking a page:" << endl;
            manager.viewLikedPages(u2.getName());
            cout << "-------homepage-------" << endl;
            homepage f1(&u1, "Enjoying in Murree", 1, "excited");
            f1.showhomepage();
            Comment* c3 = new Comment("Mariyam", "I like the view");
            Comment* c4 = new Comment("Abeeha", "Interesting!");
            c3->showComment();
            c4->showComment();
            homepage f2(&u5, "Waiting for Result", 0, "shared");
            f2.showhomepage();
            Comment* c5 = new Comment("Saad Ali", "Me too");
            Comment* c6 = new Comment("Ahsan Ali", "I am gonna fail fr");
            c5->showComment();
            c6->showComment();
            homepage f3(&u4, "I should apply for ABC intership...", 2, "future");
            f3.showhomepage();
            homepage f4(&p4, "We are celebrating 20 years for our success", 4, "success");
            f4.showhomepage();
            Comment* c7 = new Comment("Amazon", "Keep supporting us!");
            Comment* c8 = new Comment("Fatima", "WOW!");
            c7->showComment();
            c8->showComment();
            homepage f5(&p3, "Oil drilling in Alaska & #39; s indigenous communities is on the table again", 0, "shared");
            f5.showhomepage();
            // Posts
            Post* post1 = new Post(14, 3, 2025, &u2, "Just joined this awesome platform!");
            u2.createPost(post1);
            Post* post2 = new Post(15, 3, 2025, &u2, "Finals are starting");
            u2.createPost(post2);
            // Likes
            post1->likePost(&u3);
            post1->likePost(&u4);
            post1->likePost(&u3); // duplicate like test
            post2->likePost(&u1);
            post2->likePost(&u4);
            post2->likePost(&u2);
            // Comments
            Comment* c1 = new Comment("Ahsan Ali", "Congrats!");
            Comment* c2 = new Comment("Ali Ahmed", "Welcome!");
            post1->addComment(c1);
            post1->addComment(c2);
            Comment* c9 = new Comment("Ahsan Ali", "I am not prepared for that");
            post2->addComment(c9);
            // Share
            post1->sharePost();
            post2->sharePost();
            post2->sharePost();
            Post* oldPost1 = new Post(15, 3, 2024, &u2, "Outfit of the day!!");
            u2.createPost(oldPost1);
            Post* oldPost2 = new Post(15, 2, 2024, &u2, "Another memory from last year");
            u2.createPost(oldPost2);
            u2.memories(oldPost1, oldPost2);
            // View timeline
            u2.viewTimeline();
            post1->viewlikedlist();
            post2->viewlikedlist();
            u2.viewpage(&p1,&u2);
            u2.viewpage(&p3,&u2);
        }
        else if (username->getID() == "u3") {
            date d(15, 3, 2025);
            d.printdate();
            User u3("u3", "Ahsan Ali");
            u3.setUser();
            User u1("u1", "Fatima");
            User u2("u2", "Abeeha");
            User u4("u4", "Ali Ahmed");
            u3.addFriend(&u1);
            u3.addFriend(&u3);
            u3.addFriend(&u4);
            u3.viewFriendList();
            PageManage p1("p1", "Nike");
            PageManage p2("p2", "Al Jazeera");
            PageManage p3("p3", "Google");
            PageManage p4("p4", "Cristiano");
            PageManage manager("", "");
            manager.likePage(&p1);
            manager.likePage(&p2);
            manager.likePage(&p3);
            manager.likePage(&p4);
            manager.viewLikedPages(u3.getName());
            manager.dislikePage(&p2);
            cout << "After disliking a page:" << endl;
            manager.viewLikedPages(u3.getName());
            cout << "-------homepage-------" << endl;
            homepage f1(&u1, "Enjoying in Murree", 1, "excited");
            f1.showhomepage();
            Comment* c3 = new Comment("Mariyam", "I like the view");
            Comment* c4 = new Comment("Abeeha", "Interesting!");
            c3->showComment();
            c4->showComment();
            homepage f2(&u4, "check part 2 for this", 3, "art");
            f2.showhomepage();
            Comment* c5 = new Comment("Saad Ali", "waiting for part 2...");
            Comment* c6 = new Comment("Ahsan Ali", "i am in love with your paintings");
            c5->showComment();
            c6->showComment();
            homepage f3(&u4, "I should apply for ABC intership...", 2, "future");
            f3.showhomepage();
            homepage f4(&p3, "12 days until #GoogleIO!", 0, "shared");
            f4.showhomepage();
            Comment* c7 = new Comment("Mariyam", "new feature...");
            Comment* c8 = new Comment("Fatima", "WOW!");
            c7->showComment();
            c8->showComment();
            homepage f5(&p1, "The latest Nike 24.7 collection features premium fabrics in all-new hues and styles.", 0, "shared");
            f5.showhomepage();
            // Posts
            Post* post1 = new Post(14, 3, 2025, &u3, "Just joined this awesome platform!");
            u3.createPost(post1);
            Post* post2 = new Post(15, 3, 2025, &u3, "I need a vacation!!");
            u3.createPost(post2);
            // Likes
            post1->likePost(&u3);
            post1->likePost(&u4);
            post1->likePost(&u3); // duplicate like test
            post2->likePost(&u1);
            post2->likePost(&u4);
            post2->likePost(&u2);
            // Comments
            Comment* c1 = new Comment("Ahsan Ali", "Congrats!");
            Comment* c2 = new Comment("Ali Ahmed", "Welcome!");
            post1->addComment(c1);
            post1->addComment(c2);
            Comment* c9 = new Comment("Ahsan Ali", "me too");
            Comment* cc1 = new Comment("Fatima", "Murree is good!");
            post2->addComment(c9);
            post2->addComment(cc1);
            // Share
            post1->sharePost();
            post2->sharePost();
            post2->sharePost();
            Post* oldPost1 = new Post(12, 3, 2025, &u3, "Finally exams are over");
            u3.createPost(oldPost1);
            Post* oldPost2 = new Post(15, 3, 2023, &u3, "having fun!!");
            u3.createPost(oldPost2);
            u3.memories(oldPost1, oldPost2);
            // View timeline
            u3.viewTimeline();
            post1->viewlikedlist();
            post2->viewlikedlist();
            u3.viewpage(&p1, &u3);
            u3.viewpage(&p3, &u3);
            }
    }
};
int main() {
    User u1("u1", "Fatima");
    User u2("u2", "Abeeha");
    User u3("u3", "Ahsan Ali");
    socialmediarun sn(&u2);
    sn.run();
    return 0;
}
