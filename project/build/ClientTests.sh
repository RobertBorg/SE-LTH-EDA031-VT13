#!/bin/bash
#Assumes localhos

# Start server:
# ./newsserver --server-port 12393 --persistent-db false
# where 12393 is the desired port number.

#Check arguments

die () {
    echo >&2 "$@"
    exit 1
}
[ "$#" -eq 1 ] || die "1 argument required, $# provided"
echo $1 | grep -E -q '^[0-9]+$' || die "Numeric argument required, $1 provided"

echo "Showing help:"

#./newsreader --server-port $1 --server-address localhost --help
echo "Issue created, doesn't work atm"

echo "Listing newsgroups when there are no newsgroups:"

./newsreader --server-port $1 --server-address localhost list-newsgroup

echo "Creating newsgroup:"

./newsreader --server-port $1 --server-address localhost create-newsgroup MyNewsGroup

echo "Listing newsgroups:"

./newsreader --server-port $1 --server-address localhost list-newsgroup

echo "Deleting the previously created newsgroup:"

./newsreader --server-port $1 --server-address localhost delete-newsgroup 1

echo "Creating a new newsgroup:"

./newsreader --server-port $1 --server-address localhost create-newsgroup Test

echo "Attempting to delete a newsgroup that doesn't exist:"

./newsreader --server-port $1 --server-address localhost delete-newsgroup 5

echo "Listing articles from the newsgroup when there are no articles:"

./newsreader --server-port $1 --server-address localhost list-article 2

echo "Creating an article:"

./newsreader --server-port $1 --server-address localhost create-article 2 Test 'Christofer Heimonen' 'lalal lalallalalal lalal lalal all allal al lalala lala'

echo "Listing all articles from the newsgroup:"
#./newsreader --server-port $1 --server-address localhost list-article 2
echo "Issue created, doesn't work atm"

echo "Listing articles from a newsgroup that doesn't exist:"

#./newsreader --server-port $1 --server-address localhost list-article 6
echo "Issue created, doesn't work atm"

echo "Fetching the article:"

./newsreader --server-port $1 --server-address localhost get-article 2 1

echo "Deleting article:"

./newsreader --server-port $1 --server-address localhost delete-article 2 1

echo "Deleting article that doesn't exist:"

./newsreader --server-port $1 --server-address localhost delete-article 2 6

echo "Deleting article from a newsgroup that doesn't exist:"

./newsreader --server-port $1 --server-address localhost delete-article 9 1

echo "Creating an article into a newsgroup that doesn't exist:"

# ./newsreader --server-port $1 --server-address localhost create-article 10 Test 'Christofer Heimonen' 'lalal lalallalalal'
echo "Issue created, doesn't work atm"

echo "Fetching an article that doesn't exist:"

#./newsreader --server-port $1 --server-address localhost get-article 2 7
echo "Issue created, doesn't work atm"

echo "Fetching an article from a newsgroup that doesn't exist:"
#./newsreader --server-port $1 --server-address localhost get-article 7 1
echo "Issue created, doesn't work atm"

echo "Sending a command that isn't supported:"

#./newsreader --server-port $1 --server-address localhost trueThat
echo "Issue created, doesn't work atm"

exit 0
