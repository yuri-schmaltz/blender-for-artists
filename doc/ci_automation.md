# Automação de PRs, Rótulos e Releases

Este repositório possui automações via GitHub Actions para agilizar fluxos de contribuição e publicação.

## PRs com rótulos automáticos
- Workflow: .github/workflows/labeler.yml
- Configuração: .github/labeler.yml
- Sincronização de rótulos: .github/workflows/sync-labels.yml + catálogo em .github/labels.yml

O workflow `labeler` aplica rótulos conforme caminhos alterados. O `sync-labels` garante que os rótulos definidos existam no repositório.

## PR automático ao fazer push
- Workflow: .github/workflows/auto-pr-from-branch.yml

Ao fazer push para qualquer branch diferente de `master` neste repositório, um PR para `master` é aberto automaticamente com o rótulo `status:needs-triage`.

Observações:
- Funciona para branches do repositório principal (não para forks).
- Requer que nas configurações do repositório, em Settings → Actions → General, a permissão do `GITHUB_TOKEN` esteja como "Read and write permissions".

## Automação de releases
- Workflow: .github/workflows/release-please.yml

Usamos o `release-please` que:
- Cria PRs de release automaticamente a partir de commits em formato Conventional Commits.
- Ao mesclar o PR de release, cria a tag e o GitHub Release com changelog gerado.

Recomendações:
- Utilize Conventional Commits: `feat: ...`, `fix: ...`, `docs: ...`, `refactor: ...`, `perf: ...`, `build: ...`, `ci: ...`, `chore: ...`.
- Opcional: padronize nomes de branch (ex.: `feat/...`, `fix/...`, `docs/...`) para melhor triagem.

## Permissões necessárias
Em Settings → Actions → General:
- Workflow permissions: marque "Read and write permissions".
- Allow GitHub Actions to create and approve pull requests: habilite quando disponível.

## Dúvidas comuns
- Labels não aplicam? Rode manualmente o workflow _Sync Labels_ (Workflow Dispatch) para criar/atualizar rótulos.
- Releases não geram? Verifique se os commits seguem Conventional Commits. Você também pode disparar o _Release Please_ manualmente.
