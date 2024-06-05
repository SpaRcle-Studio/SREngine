print("CloseMacro.py script is running...")

try:
    import os
    import re
    from github import Github
    from github import Auth
except ImportError:
    print("Import exception occurred!")
    exit(0)

commitMessage = os.getenv('commitMessage')
commitSha = os.getenv('commitSha')
token = os.getenv('ciToken')

try:
    print("Trying to login to GitHub and get the repository")
    auth = Auth.Token(token)
    g = Github(auth=auth)
    repo = g.get_repo("SpaRcle-Studio/SREngine")
except Exception as e:
    print(f"GitHub login exception occurred: {str(e)}")
    exit(0)

print(f"Commit message:\n{commitMessage}\n")

issueIds = []

try:
    regexClose = re.search('#SR_CLOSE(.*)', commitMessage)
    if regexClose != None:
        closeMacros = regexClose.group(1)
        closeMacros = closeMacros[1:][:-1]
        closeMacros = closeMacros.replace(' ', '')
        issueIds = closeMacros.split(",")
        print(f"Issue Ids are: {issueIds}")
except Exception as e:
    print(f"Regex error occurred: {str(e)}")

for issueId in issueIds:
    try:
        print(f"Trying to get issue: {issueId}")
        issue = repo.get_issue(int(issueId))
        print(f"Creating comment and closing issue: {issueId}")
        issue.create_comment(f"Issue is closed automatically by CI. Commit: {commitSha}")
        issue.edit(state='closed')
        print(f"Success for issue: {issueId}")
    except Exception as e:
        print(f"Issue managing exception occurred: {str(e)}")
        
print(f"Script execution is finished.")