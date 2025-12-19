# ONDA 2 Status Report

## 📊 Progresso: Design System Foundation

**Data Início:** 2025-12-19  
**Fase Atual:** Inicial (tokens scaffolding)

---

## ✅ Completados

### Design Tokens Architecture
- [x] Header com structs semânticas (colors, spacing, borders, typography, button)
- [x] Implementação com valores default (light theme baseline)
- [x] API global e funções getter
- [x] Documentação ONDA 2

---

## 🔜 Em Progresso & Planejado

### PATCH 2: Button Style Consolidation
- [ ] Criar macros para variantes de botões
- [ ] Consolidar estilos (PRIMARY, SECONDARY, TERTIARY, DANGER, GHOST)
- [ ] Integrar spacing tokens

### PATCH 3: Token Integration
- [ ] Integrar tokens em `ui_draw_but()` para min_height, radius
- [ ] Usar `tokens->typography` em text rendering
- [ ] Atualizar focus ring para usar `tokens->colors.focus_ring`

### Theme Mapping
- [ ] Mapear `bTheme` wcol_* para tokens semânticos
- [ ] Testar com temas escuro/claro

---

## 📈 Métricas

| Métrica | Valor |
|---------|-------|
| Tokens definidos | 23 |
| Variantes de botão | 5 |
| Cores semânticas | 10 |
| Espaçamentos | 6 |

---

## 🎯 Próximos Passos (ONDA 2 Fase 2)

1. Consolidar estilos de botões com helpers reutilizáveis
2. Integrar tokens no pipeline de rendering
3. Validar com visual regression tests
4. Documentar padrões para novos componentes
5. Fazer merge e publicar ONDA 2 completo
