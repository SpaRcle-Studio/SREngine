print("AutoIssues.py script is running...")

import os
import re

try:
    from github import Github
    from github import Auth
except ImportError:
    subprocess.run([sys.executable, 'pip', 'install', 'pygithub'])
    subprocess.run([sys.executable, '-m', 'pip', 'install', 'pygithub'])
    from github import Github
    from github import Auth

def getIssueBranch(issue):
    body = issue.body
    if body == None:
        return None

    regex = re.search('Commit Branch: `(.*)`', body)
    if regex != None:
        return regex.group(1)
    return None

commitBranch = os.getenv('commitBranch')
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

issues = repo.get_issues(state='open', labels=['build-failed'])

for issue in issues:
    if issue.state == 'closed':
        continue

    issueBranch = getIssueBranch(issue)

    if issueBranch == None:
        print(f"Branch information is not found for issue: {issue.number}")
        continue

    if issueBranch == commitBranch:
        try:
            print(f"Creating comment and closing issue: {issue.number}")
            issue.create_comment(f"Build is successful now. Commit: {commitSha}")
            issue.edit(state='closed')
            print(f"Success for issue: {issue.number}")
        except Exception as e:
            print(f"Issue managing exception occurred: {str(e)}")

print(f"Script execution is finished.")