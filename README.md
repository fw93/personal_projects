# Jinhyuk Jeon's personal projects

**Reorganized project repositories**

> inspired while talking with linecorp interviewers(devs). Documentation and proper SCM habits are important as a developer.

## using git

* basic configs(required on first use)

`git config --global user.name "{{username}}"`
    
 `git config --global user.email "{{email}}"`

* stage changes

`git add *`

* stage deletes also

`git add -u`

* commit changes

`git commit -m "{{message with commit}}"`

* undo commits

`git commit -m "{{reverting message}}`

* make new branch

`git branch {{newbranch}}`

* check all branch lists

`git branch -r`

* move to new branch

`git checkout {{branch-to-go}}`

* merge branches ( first be at branch to receive merge )

`git merge {{branchname}}`

* receive updates from remote

`git pull`

* update changes to remote

`git push origin master`

## basic markdown

* h1 ~ h6

`# ~ ######`
    
* indented text

`\> {{text}}`
    
* code

`\`{{code}}\`
    
* links

`[{{link text}}]({{link address}})`
    
* emojis

`:cry:`
    
[check out emoji cheetsheet](https://gist.github.com/roachhd/1f029bd4b50b8a524f3c)


> [markdown reference from here](https://gist.github.com/ihoneymon/652be052a0727ad59601)
