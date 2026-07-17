# Contributing

Thanks for helping improve these SQL notes.

## Adding a new note

1. Find the right numbered section under the repo root (or propose a new one via an
   issue if it doesn't fit).
2. Copy the standard template structure used across the repo:
   - Overview
   - Key Points
   - Example
   - Common Pitfalls
   - Related Topics
   - References
3. Keep filenames lowercase, hyphenated, and numbered to preserve reading order
   (e.g. `05-joining-multiple-tables.md`).

## Style guidelines

- Prefer runnable SQL examples over abstract descriptions.
- Note which database engine an example targets if it isn't ANSI-standard SQL.
- Keep diagrams in `assets/diagrams/` and reference them with relative links.
- Cross-link related notes instead of duplicating explanations.

## Pull requests

- One topic per PR where possible.
- Use the PR template checklist.
- Link the related issue if one exists.

## Reporting problems

Use the issue templates under `.github/ISSUE_TEMPLATE/` for bug reports (incorrect
information) or feature requests (missing topics).
