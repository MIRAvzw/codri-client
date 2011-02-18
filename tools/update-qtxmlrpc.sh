#!/bin/sh

[ -d .git ] || { echo ! Call this script from the repository root; exit 1; }

echo '* Updating SVN'
git checkout qtxmlrpc-git

echo '* Updating tracking branch'
git merge qtxmlrpc-svn
git push origin HEAD

echo '* Updating master'
git checkout master
cd lib/qtxmlrpc
git pull origin qtxmlrpc-git
cd ..
git add qtxmlrpc

echo '* Done! Please verify, and commit if needed.'
